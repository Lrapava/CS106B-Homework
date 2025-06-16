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

int main() {

	// making sure RNG seed changes
	srand(time(NULL));
	
	uint16_t flipCounter = 0;
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
			printf("heads\n");
		} else {
			last3flips = last3flips &~(1 << (flipCounter % 3));
			printf("tails\n");
		}

		random_num >>= 1;
	}

	// detecting integer overflow
	if (flipCounter == 0) {
		printf("Fascinating, 65535 flips was not enough!\n");
	} else {
		printf("It took %d flips to get 3 consecutive heads.\n", flipCounter);
	}
	
}
