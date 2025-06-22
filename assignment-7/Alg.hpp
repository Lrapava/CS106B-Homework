#ifndef ALG_HPP
#define ALG_HPP

#include <functional>
#include <string>
#include <vector>
#include <map>

extern std::map<std::string, std::function<void()>> algLib;

#define Coord std::pair <int, int>
#define Grid std::vector<std::vector <double>> 

void initAlgLib();

#endif
