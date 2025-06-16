/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(std::string::iterator textStart, std::string::iterator textEnd, std::string::iterator subsStart, std::string::iterator startEnd);
bool isSubsequence(std::string text, std::string subs);

int main(int argn, char* argv[]) {

	std::string txt, sub;

	if (argn == 3) {
		txt = std::string(argv[1]);
		sub = std::string(argv[2]);
	} else {
		std::cin >> txt >> sub;
	}
	
	std::cout << isSubsequence(txt, sub) << "\n";
}

bool isSubsequence(std::string::iterator textStart, std::string::iterator textEnd, std::string::iterator subsStart, std::string::iterator subsEnd) {

	if (subsStart == subsEnd) return true;
	if (textStart == textEnd) return false;

	if (*textStart == *subsStart) {
		return isSubsequence(std::next(textStart), textEnd, std::next(subsStart), subsEnd);
	}

	return isSubsequence(std::next(textStart), textEnd, subsStart, subsEnd);
	
}

bool isSubsequence(std::string text, std::string subs) {
	return isSubsequence(text.begin(), text.end(), subs.begin(), subs.end());
}
