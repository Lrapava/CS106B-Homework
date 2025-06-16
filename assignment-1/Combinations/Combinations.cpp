/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>

int C(int n, int m) {
	if (m % n == 0) {
		return 1;
	}
	return C(n-1, m) + C(n-1, m-1);
}

int main() {
	int n, m;
	std::cin >> n >> m;
	std::cout << C(n, m) << "\n";
	return 0;
}
