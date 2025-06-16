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
#include <string_view>

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(std::string& text, std::string& subs);

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

bool isSubsequence(std::string& text, std::string& subs) {

	if (subs == "") return true;
	if (text == "") return false;

	std::string newText = text.substr(1);
	std::string newSubs;

	if (text[0] == subs[0]) {
		newSubs = subs.substr(1);
	} else {
		newSubs = subs;
	}
	
	return isSubsequence(newText, newSubs);
}
