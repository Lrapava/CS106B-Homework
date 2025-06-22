#include <cmath>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>

#include "Alg.hpp"
#include "State.hpp"

std::map<std::string, std::function<void()>> algLib;

#define Coord std::pair <int, int>
#define Grid std::vector<std::vector <double>> 

#define inf std::numeric_limits<double>::infinity()

std::vector<Coord> shortestPath(Coord start, Coord end, const Grid& world,
	std::function<double(Coord, Coord, const Grid&)> cost,
	std::function<double(Coord, Coord, const Grid&)> heuristic
) {

	State::attempts = 0;

	int rows = world.size();
	int cols = rows > 0 ? world[0].size() : 0;

	const std::vector<Coord> directions = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1},          { 0, 1},
		{ 1, -1}, { 1, 0}, { 1, 1}
	};

	std::map<Coord, double> dist;
	std::map<Coord, Coord> parent;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			dist[{r, c}] = inf;
		}
	}

	using PQElem = std::pair <double, std::pair <int, int>>;
	std::priority_queue<PQElem, std::vector<PQElem>, std::greater<PQElem>> pq;

	dist[start] = 0;
	pq.push({heuristic(start, end, world), start});

	while (!pq.empty()) {
		Coord cur = pq.top().second;
		pq.pop();
		State::attempts++;

		if (cur == end) {
			std::vector<Coord> path;
			for (Coord at = end; at != start; at = parent[at]) {
				path.push_back(at);
			}
			path.push_back(start);
			std::reverse(path.begin(), path.end());
			return path;
		}
		double curDist = dist[cur];
		for (const Coord& delta : directions) {
			Coord neigh = {cur.first + delta.first, cur.second + delta.second};
			if (neigh.first  >= 0 && neigh.first  < rows  && 
				neigh.second >= 0 && neigh.second < cols) {
				double stepCost = cost(cur, neigh, world);
				if (stepCost != inf) {
					double newDist = stepCost + curDist;
					if (newDist < dist[neigh]) {
						dist[neigh] = newDist;
						parent[neigh] = cur;
						pq.push({newDist + heuristic(neigh, end, world), neigh});
					}
				}
			}
		}
	}
	return std::vector<Coord>();
}

double terrainCost(Coord a, Coord b, const Grid& world) {
	double directionCost = (a.first != b.first && a.second != b.second) ? std::sqrt(2.0) : 1.0;
	return directionCost + std::abs(world[b.first][b.second] - world[a.first][a.second]);
}

double terrainHeuristicAStar(Coord a, Coord b, const Grid&) {
	double dx = a.first - b.first;
	double dy = a.second - b.second;
	return std::sqrt(dx * dx + dy * dy);
}

double mazeCost(Coord a, Coord b, const Grid& world) {
	if (world[b.first][b.second] < 0.1) return inf;
	if (a.first != b.first && a.second != b.second) return inf;
	return 1.0;
}

double mazeHeuristicAStar(Coord a, Coord b, const Grid&) {
	return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

double zeroHeuristic(Coord a, Coord b, const Grid&) {
	return 0.0;
}

void initAlgLib() {
	algLib["dijkstra"] = [](){
		if (State::mode == "maze") {
			State::resultedPath = shortestPath(
				{State::coord[0], State::coord[1]}, 
				{State::coord[2], State::coord[3]},
				State::world,
				mazeCost,
				zeroHeuristic
			);
		} else {
			State::resultedPath = shortestPath(
				{State::coord[0], State::coord[1]}, 
				{State::coord[2], State::coord[3]},
				State::world,
				terrainCost,
				zeroHeuristic
			);
		}
	};
	algLib["astar"] = [](){
		if (State::mode == "maze") {
			State::resultedPath = shortestPath(
				{State::coord[0], State::coord[1]}, 
				{State::coord[2], State::coord[3]},
				State::world,
				mazeCost,
				mazeHeuristicAStar
			);
		} else {
			State::resultedPath = shortestPath(
				{State::coord[0], State::coord[1]}, 
				{State::coord[2], State::coord[3]},
				State::world,
				terrainCost,
				terrainHeuristicAStar
			);
		}
	};
}
