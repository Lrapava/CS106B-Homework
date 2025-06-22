#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

#include "State.hpp"
#include "Cmd.hpp"
#include "Alg.hpp"
#include "DisjointSetUnion.hpp"

std::map <std::string, Command> cmdLib;

bool isNonNegativeNumber(const std::string& s) {
	if (s.empty()) return false;
	for (char c : s) {
		if (!std::isdigit(c)) return false;
	}
	return true;
}

void initCmdLib() {
	cmdLib["!quit"] = Command([](const std::vector <std::string>& args) {
		State::isRunning = false;
	}, 1, "Exits program");

	cmdLib["help"] = Command([](const std::vector <std::string>& args) {
		for (auto args : cmdLib) {
			if (args.second.getArgc() == 1) {
				std::cout << args.first <<  " - " << args.second.getDesc() << "\n";
			} else {
				std::cout << args.first << " (" << args.second.getArgc()-1 << ") - " << args.second.getDesc() << "\n";
			}
		}
	}, 1, "Displays this message");

	cmdLib["load"] = Command([](const std::vector <std::string>& args) {
		std::ifstream file(args[1]);
		if (file.is_open()) {
			State::loadMap(file);
			std::cout << args[1] << " is fully loaded.\n";
			if (State::visible) {
				cmdLib["show-map"].execute({"show-map"});
			}
		} else {
			std::cerr << "Could not open file.\n";
		}
		file.close();
	}, 2, "Loads maze or terrain from a file.");
	
	cmdLib["reset"] = Command([](const std::vector <std::string>& args) {
		State::reset();
	}, 1, "Resets state to initial state");

	cmdLib["state"] = Command([](const std::vector <std::string>& args) {
		std::cout << "mode: " << State::mode << "\n";
		std::cout << "dimensions: " << State::worldSize[0] << "x" << State::worldSize[1] << "\n";
		std::cout << "algorithm: " << State::algm << "\n";
		std::cout << "start: (" << State::coord[0] << ", " << State::coord[1] << ")\n";
		std::cout << "destination: (" << State::coord[2] << ", " << State::coord[3] << ")\n";
	}, 1, "Displays state.");

	cmdLib["sd"] = Command([](const std::vector <std::string>& args) {
		if (State::mode != "-") {
			bool allValid = true;
			for (int i = 1; i < 5 && allValid; i++) {
				if (!isNonNegativeNumber(args[i]) || std::stoi(args[i]) >= State::worldSize[(i+1)%2]) {
					allValid = false;
				}
			}
			// if (allValid && State::mode == "maze") {
				// bool p1 = State::maze[std::stoi(args[1])][std::stoi(args[2])];
				// bool p2 = State::maze[std::stoi(args[3])][std::stoi(args[4])];
				// allValid = allValid && p1 && p2;
			// }
			if (allValid) {
				for (int i = 1; i < 5; i++) {
					State::coord[i-1] = std::stoi(args[i]);
				}
			} else {
				std::cerr << "Error: impropper coordinates.\n";
			}
		} else {
			std::cerr << "Error: map was not loaded.\n";
		}
	}, 5, "Sets start and destination");
	
	cmdLib["set-alg"] = Command([](const std::vector <std::string>& args) {
		if (algLib.find(args[1]) != algLib.end()) {
			State::algm = args[1];
		} else {
			std::cerr << "Algorithm not found.\n";
		}
	}, 2, "Used to choose an algorithm.");

	cmdLib["list-alg"] = Command([](const std::vector <std::string>& args) {
		for (auto alg : algLib) {
			std::cout << alg.first << "\n";
		}
	}, 1, "Lists all available algorithms.");

	cmdLib["solve"] = Command([](const std::vector <std::string>& args) {
		if (algLib.find(State::algm) != algLib.end()) {
			State::resultedPath.clear();
			algLib[State::algm]();
			if (State::visible) {
				cmdLib["show-path"].execute({"show-path"});
			}
			std::cout << "Path length: " << State::resultedPath.size() << ", Squares visitted: " << State::attempts << "\n";
		} else {
			std::cerr << "Algorithm not found.\n";
		}
	}, 1, "Solves the maze using selected algorithm.");

	cmdLib["export-map"] = Command([](const std::vector <std::string>& args) {

		if (State::worldSize[0] == 0 || State::worldSize[1] == 0) {
			std::cerr << "Please load or generate a map first.\n";
			return;
		}
		
		std::ofstream file(args[1]);
		if (file.is_open()) {
			file << "P3\n";
			file << State::worldSize[0] << " " << State::worldSize[1] << "\n";
			file << "255\n";

			for (int i = 0; i < State::worldSize[0]; i++) {
				for (int j = 0; j < State::worldSize[1]; j++) {
					const double k = State::world[i][j];
					file << (int)(k*255) << " " << (int)(k*255) << " " << (int)(k*255) << " ";
				}
				file << "\n";
			}
		} else {
			std::cerr << "Could not open file\n";
		}
		file.close();
	}, 2, "Exports map.");

	cmdLib["export-path"] = Command([](const std::vector <std::string>& args) {

		if (State::worldSize[0] == 0 || State::worldSize[1] == 0) {
			std::cerr << "Please load or generate a map first.\n";
			return;
		}
		
		if (State::algm == "-" || State::worldSize[0] == 0 || State::worldSize[1] == 0) {
			std::cerr << "Please select algorithm, valid start position and destination.\n";
			return;
		}

		std::ofstream file(args[1]);
		if (file.is_open()) {
			file << "P3\n";
			file << State::worldSize[0] << " " << State::worldSize[1] << "\n";
			file << "255\n";

			for (int i = 0; i < State::worldSize[0]; i++) {
				for (int j = 0; j < State::worldSize[1]; j++) {
					if (std::find(State::resultedPath.begin(), State::resultedPath.end(),
						std::pair<int, int>(i, j)) == State::resultedPath.end()) {
						const double k = State::world[i][j];
						file << (int)(k*255) << " " << (int)(k*255) << " " << (int)(k*255) << " ";
					} else {
						file << "70 140 210 ";
					}
				}
				file << "\n";
			}
		} else {
			std::cerr << "Could not open file\n";
		}
		file.close();
	}, 2, "Exports map with solution.");

	cmdLib["show-map"] = Command([](const std::vector <std::string>& args) {
		for (int i = 0; i < State::worldSize[0]; i++) {
			for (int j = 0; j < State::worldSize[1]; j++) {
				std::cout << State::grad[round((State::grad.size()-1)*State::world[i][j])];
				std::cout << State::grad[round((State::grad.size()-1)*State::world[i][j])];
			}
			std::cout << "\n";
		}

	}, 1, "Displays map");

	cmdLib["show-path"] = Command([](const std::vector <std::string>& args) {
		for (int i = 0; i < State::worldSize[0]; i++) {
			for (int j = 0; j < State::worldSize[1]; j++) {
				if (std::find(
						State::resultedPath.begin(), 
						State::resultedPath.end(),
						std::pair<int, int>(i, j) 
					) == State::resultedPath.end()) {
					std::cout << State::grad[round((State::grad.size()-1)*State::world[i][j])];
					std::cout << State::grad[round((State::grad.size()-1)*State::world[i][j])];
				} else {
					std::cout << "██";
				}
			}
			std::cout << "\n";
		}

	}, 1, "Displays map");

	cmdLib["visible"] = Command([](const std::vector <std::string>& args) {
		State::visible = true;
	}, 1, "Makes maps & paths visible by default");


	cmdLib["invisible"] = Command([](const std::vector <std::string>& args) {
		State::visible = false;
	}, 1, "Makes maps & paths not visible by default");

	cmdLib["random"] = Command([](const std::vector <std::string>& args) {
		State::reset();

		State::mode = "maze";
		State::worldSize[0] = std::stoi(args[1]);
		State::worldSize[1] = std::stoi(args[2]);

		if (std::min(State::worldSize[0], State::worldSize[1]) > 0) {
			State::world.resize(State::worldSize[0]);
			for (int i = 0; i < State::worldSize[0]; i++) {
				State::world[i].resize(State::worldSize[1], 0);
			}

			std::vector <std::pair <Coord, Coord>> edges;
			std::vector <Coord> rooms;
			std::map <Coord, dsu_node> DSU;

			for (int i = 0; i < State::worldSize[0]; i+=2) {
				for (int j = 0; j < State::worldSize[1]; j+=2) {
					State::world[i][j] = 1;
					rooms.push_back({i, j});
				}
			}


			auto inb = [](Coord a){
				return a.first >= 0 && a.first <= State::worldSize[0] &&
					a.second >= 0 && a.second <= State::worldSize[1];
			};

			for (int i = 0, l = rooms.size(); i < l; i++) {
				auto n1 = rooms[i]; n1.first += 2;
				auto n2 = rooms[i]; n2.second += 2;
				if (inb(n1)) {
					edges.push_back({rooms[i], n1});
				}
				if (inb(n2)) {
					edges.push_back({rooms[i], n2});
				}
			}

			unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
			std::mt19937 rng(seed);
			std::shuffle(edges.begin(), edges.end(), rng);

			auto avg = [](Coord a, Coord b){
				Coord c;
				c.first = (a.first + b.first) / 2;
				c.second = (a.second + b.second) / 2;
				return c; 
			};

			for (auto e : edges) {
				if (unite(DSU[e.first], DSU[e.second])) {
					auto a = avg(e.first, e.second);
					State::world[a.first][a.second] = 1;
				}
			}
			State::coord[0] = State::coord[1] = 0;
			State::coord[2] = State::worldSize[0] - 1;
			State::coord[3] = State::worldSize[1] - 1;
			if (State::visible) {
				cmdLib["show-map"].execute({"show-map"});
			}
		} else {
			std::cerr << "Invalid dimensions.\n";
			State::reset();
		}
		
	}, 3, "generates random maze.");

}
