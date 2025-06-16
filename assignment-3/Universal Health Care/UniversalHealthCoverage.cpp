/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include <set>
#include <vector>

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(std::set <std::string>& cities,
                               std::vector <std::set <std::string>>& locations,
                               int numHospitals,
                               std::vector< std::set<std::string> >& result);


int main() {
	std::set <std::string> cities = { "A", "B", "C", "D", "E", "F" };
	std::vector <std::set <std::string>> locations = { {"A", "B", "C"}, {"A", "C", "D"}, {"B", "F"}, {"C", "E", "F"} };

	for (int i = 1, l = locations.size(); i <= l; i++) {
		std::vector <std::set <std::string>> result;
		bool res = canOfferUniversalCoverage(cities, locations, i, result);
		std::cout << i << ": " << res << "\n";
		if (res) {
			std::cout << "{ ";
			for (auto x : result) {
				std::cout << "{ ";
				for (auto y : x) {
					std::cout << y << " ";
				}
				std::cout << "} ";
			}
			std::cout << "}\n";
		}
	}

    return 0;
}

bool canOfferUniversalCoverage(std::set <std::string>& cities, std::vector <std::set <std::string>>& locations, 
	int numHospitals, std::vector<std::set<std::string>>& result) {

	if (cities.size() == 0) {
		return true;
	}

	if (numHospitals == 0) {
		return false;
	}
	
	for (std::set <std::string> loc : locations) {
		std::vector <std::set <std::string>> newLocations;

		for (std::set <std::string> l: locations) {
			if (l != loc) {
				newLocations.push_back(l);
			}
		}

		std::set <std::string> newCities = cities;
		for (std::string city : loc) {
			newCities.erase(city);
		}

		if (canOfferUniversalCoverage(newCities, newLocations, numHospitals-1, result)) {
			result.push_back(loc);
			return true;
		}
		
	}

	return false;
	
}
