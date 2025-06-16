/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#define BENCH_LIMIT (1<<25)

// messing with macros
/*

constexpr uint8_t ilog2(uint64_t n) {
	uint8_t res = 0;
	while (n > 0) {
		res++;
		n >>= 1;
	}
	return res;
}

constexpr uint8_t N_RANDOM_BITS = ilog2(RAND_MAX);

#if N_RANDOM_BITS >= 32
uint64_t random_num = 0;
#elif N_RANDOM_BITS >= 16
uint32_t random_num = 0;
#else
uint16_t random_num = 0;
#endif

int benchmark() {

	uint32_t flipCounter = 0;
	uint8_t last3flips = 0;

	while (last3flips != 7 && ++flipCounter != 0) {

		// generating new random number every 16 flips 
		if (flipCounter % N_RANDOM_BITS == 1) {
			random_num = rand();
		}

		// storing & outputting result
		if (random_num % 2) {
			last3flips = last3flips | (1 << (flipCounter % 3));
		} else {
			last3flips = last3flips &~(1 << (flipCounter % 3));
		}

		random_num >>= 1;
	}
	
	return flipCounter;
	
}
// */

// /*
int benchmark() {

	uint32_t flipCounter = 0;
	uint16_t random_num = 0;
	uint8_t last3flips = 0;

	while (last3flips != 7 && ++flipCounter != 0) {

		// generating new random number every 16 flips
		if (flipCounter % 16 == 1) {
			random_num = rand();
		}

		// storing & outputting result
		if (random_num % 2) {
			last3flips = last3flips | (1 << (flipCounter % 3));
		} else {
			last3flips = last3flips &~(1 << (flipCounter % 3));
		}

		random_num >>= 1;
	}
	
	return flipCounter;	
}
// */

int main() {

	srand(time(NULL));
	std::map <int, int> mp;

	for (int i = 0; i < BENCH_LIMIT; i++) {
		int result = benchmark();
		mp[result]++;
	}

	for (auto x : mp) {
		printf("%d %d\n", x.first, x.second);
	}

	printf("%d simulated\n", BENCH_LIMIT);
	
}
