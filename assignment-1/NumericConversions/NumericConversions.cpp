/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <climits>

#define ll long long

/* Function prototypes */

std::string intToString(int n);
int stringToInt(std::string str);

/* Main program */

int main() {

	srand(time(NULL));

	// manual testing till 111 is received
	int n = 0;
	while (n != 111) {
		std::cin >> n;
		std::cout << stringToInt(intToString(n)) << "\n";
	}
	
	// testing indefinitely
	for(;;) {
		ll x = rand();
		x = (1-2*(x%2)) * (x/2);
		std::cout << "Testing " << x << "\n";
		if (stringToInt(intToString(x)) != x) {
			std::cout << "Wrong answer on: " << x << "\n";
		}
	}

}

// Converts an integer to a string
std::string intToString(int n) {
	if (n == INT_MIN) {
		return "-2147483648";
	}
	if (n < 0) {
		return "-"+intToString(-n);
	}
	std::string s = "0";
	s[0] += n%10;
	if (n/10 != 0) {
		return intToString(n/10) + s;
	}
	return s;
}

// Converts a string to an integer
int stringToInt(std::string str) {
	int n = str.size();
	if (n == 0) {
		return 0;
	}
	if (str[0] == '-') {
		return -stringToInt(str.substr(1));
	}
	return stringToInt(str.substr(0, n-1)) * 10 + (str[n-1]-'0');
}

