/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>

// uncomment line bellow for optimization
// consider these being separate files if it matters for extension points.

// #define STORE_CACHE

#ifdef STORE_CACHE
#include <map>
std::map <std::pair <int, int>, int> cache;
#endif

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);

int main() {
	int street, avenue;
	std::cin >> street >> avenue;
	std::cout << numPathsHome(street, avenue) << "\n";
    return 0;
}

int numPathsHome(int street, int avenue) {

	// error value
	if (street < 1 || avenue < 1) {
		return -1;
	}

	if (street == 1 || avenue == 1) {
		return 1;
	}

	#ifdef STORE_CACHE
	if (street > avenue) {
		std::swap(street, avenue);
	}
	if (cache.find({street, avenue}) == cache.end()) {
		cache[{street, avenue}] = numPathsHome(street-1, avenue) + numPathsHome(street, avenue-1);
	}

	return cache[{street, avenue}];

	#else
	return numPathsHome(street-1, avenue) + numPathsHome(street, avenue-1);
	#endif
}
