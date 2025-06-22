#include "State.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace State {

std::vector <std::vector <double>> world;

int worldSize[2];
int coord[4];

int attempts;

bool visible = true;

std::string algm;
std::string mode;

std::vector <Coord> resultedPath;

bool isRunning;

void reset() {
	attempts = 0;
	mode = "-";
	world.clear();
	worldSize[0] = worldSize[1] = 0;
	for (int i = 0; i < 4; i++) {
		coord[i] = 0;
	}
	// algm = "-";
	isRunning = true;
}

void loadMap(std::istream& data) {
	reset();
	data >> mode >> worldSize[0] >> worldSize[1];
	world.resize(worldSize[0]);
	for (int i = 0; i < worldSize[0]; i++) {
		world[i].resize(worldSize[1]);
	}
	for (int i = 0; i < worldSize[0]; i++) {
		for (int j = 0; j < worldSize[1]; j++) {
			data >> world[i][j];
		}
	}
	coord[0] = coord[1] = 0;
	coord[2] = worldSize[0] - 1;
	coord[3] = worldSize[1] - 1;
}

}
