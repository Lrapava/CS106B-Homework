/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: Andria Kobaidze
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

// NOTE: THIS CODE IS SO INTENSIVE IT MIGHT FREEZE YOUR COMPUTER.
// IT DID FOR SURE CAUSE A FREEZE ON MINE. MAKE SURE YOU SAVE ALL
// PROGRESS OR MODIFY THE PROGRAM BEFORE RUNNING IT. 

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <set>

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */

#define N_RAND_BITS 16
#define POWER_LIMIT 15
#define LOOPS 100

std::set<int32_t> randomSubsetOf(std::set<int32_t>& s);
std::set<int32_t> N(int32_t n);

int main() {

	srand(time(NULL));

	for (int32_t i = 0; i < LOOPS; i++) {
		std::set <int32_t> st = N(1<<POWER_LIMIT);
		std::set <int32_t> res = randomSubsetOf(st);
	}
	
    return 0;
}

std::set <int32_t> N(int n) {
	std::set <int32_t> res;
	for (int i = 1; i <= n; i++) {
		res.insert(i);
	}
	return res;
}

std::set<int> randomSubsetOf(std::set<int>& s) {

	std::set<int> st = s;
	st.erase(st.begin());
	
	std::set<int> res = randomSubsetOf(st);
	
	if (rand() % 2) {
		st.insert(*s.begin());
	}

	return res;

}
