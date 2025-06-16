/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: Andria Kobaidze
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

// This program achieves the same as unoptimized version, except it
// takes way less computational resources and does not cause your
// computer to crash

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

std::set<int32_t> randomSubsetOf(std::set<int32_t>::iterator begin, std::set<int32_t>::iterator end);
std::set<int32_t> randomSubsetOf(std::set<int32_t>& s);
std::set<int32_t> N(int32_t n);
bool myRandBit();

int main() {

	srand(time(NULL));
	std::set <int32_t> st = N(1<<POWER_LIMIT);

	for (int32_t i = 0; i < LOOPS; i++) {
		std::set <int32_t> res = randomSubsetOf(st);
	}

	auto sub = randomSubsetOf(st);
	for (auto x : sub) {
		std::cout << x << " ";
	}

	std::cout << "\n";

    return 0;
}

uint32_t randVal = 0;
uint8_t counter = 0;

bool myRandBit() {
	if ((counter % N_RAND_BITS) == 0) {
		counter = 0;
		randVal = rand();
	}
	bool res = randVal % 2;
	randVal >>= 1;
	return res;
}

std::set <int32_t> N(int n) {
	std::set <int32_t> res;
	for (int i = 1; i <= n; i++) {
		res.insert(i);
	}
	return res;
}

std::set<int32_t> randomSubsetOf(std::set<int32_t>& s) {
	return randomSubsetOf(s.begin(), s.end());
}

std::set<int32_t> randomSubsetOf(std::set<int32_t>::iterator begin, std::set<int32_t>::iterator end) {

	if (begin == end) {
		return {};
	}

	if (myRandBit()) {
		return randomSubsetOf(std::next(begin), end);
	}
	
	std::set <int32_t> res = randomSubsetOf(std::next(begin), end);
	res.insert(*begin);
	return res;
	
}
