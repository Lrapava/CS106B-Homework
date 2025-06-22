#ifndef STATE_HPP
#define STATE_HPP

#include <set>
#include <string>
#include <vector>
#include <istream>

namespace State {

extern std::vector <std::vector <double>> world;
extern int worldSize[2];
extern int coord[4];
extern std::string algm;
extern std::string mode;
extern bool isRunning;
extern int attempts;
extern bool visible;

#define Coord std::pair <int, int>
#define Grid std::vector<std::vector <double>> 

extern std::vector <Coord> resultedPath;

void reset();
void loadMap(std::istream& data);

// const std::string grad = "@&%QWNM0gB$#DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|(7J)vTLs?z/*cr!+<>;=^,_:'-.` ";
// const std::string grad = " .,:ilwW";
// const std::string grad = "@%#*+=-:. ";
const std::string grad = " .:-=+*#%@";

}

#endif
