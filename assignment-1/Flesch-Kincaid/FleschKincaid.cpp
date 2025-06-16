/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <ctype.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <map>

// default coefficients
const double C[] = { -15.59, 0.39, 11.8 };

// error messages 
std::map <int, std::string> err_msg = {
	{ 0, "" },
	{ -1, "File not found." }
};

// evaluation report struct
struct evaluationReport {
	int words = 0;
	int sentences = 0;
	int syllables = 0;
	double grade = 0;
	int error_code = 0;
	std::string filePath = "";
};

// checks if file exists
bool fileExists(std::string filePath);
// checks if given character is a vowel
inline bool isVowel(char c);
// checks if given character ends a sentence
inline bool isSentenceBreak(char c);
// tokenizer
std::vector <std::string> tokenize(std::istream &input);
// counts syllables
inline int countSyllables(std::string s);
// evaluates input from istream
evaluationReport evaluateStream(std::istream &input);
// evaluates input from a file
evaluationReport evf(std::string filePath);
// iterates input stream and processes each string in certain way
void iterateStream(std::istream &input, std::function <void(std::string)> process);
// displays help message
inline void displayHelpMessage();
// displays report
void displayReport(evaluationReport report, bool detailed);

// made the main function command-line friendly
int main(int argn, char *argv[]) {

	int arg_itr = 1;
	
	if (arg_itr >= argn) {
		iterateStream(std::cin, [](std::string f) { displayReport(evf(f), false); });		
	} else {
		if (std::string(argv[arg_itr]) == "-d" || std::string(argv[arg_itr]) == "--detailed") {
			arg_itr++;
		}
		if (arg_itr >= argn) {
			iterateStream(std::cin, [](std::string f) { displayReport(evf(f), true); });
		} else {
			if (std::string(argv[arg_itr]) == "--help" || std::string(argv[arg_itr]) == "-h") {
				displayHelpMessage();
			} else if (std::string(argv[arg_itr]) == "-i" || std::string(argv[arg_itr]) == "--input") {
				for (int i = arg_itr + 1; i < argn; i++) {
					displayReport(evf(argv[i]), arg_itr == 2);
				}
			} else if (std::string(argv[arg_itr]) == "-p" || std::string(argv[arg_itr]) == "--pathFile") {
				for (int i = arg_itr + 1; i < argn; i++) {
					std::ifstream file; 
					file.open(argv[i]);
					iterateStream(file, [arg_itr](std::string f) { displayReport(evf(f), arg_itr == 2); });
					file.close();
				}
			} else if (std::string(argv[arg_itr]) == "-r" || std::string(argv[arg_itr]) == "--raw") {
				displayReport(evaluateStream(std::cin), arg_itr == 2);
			} else {
				std::cout << "Wrong command line arguments.\n";
				std::cout << "Try `FleschKincaid --help` for help.\n";
			}
		}
	}
}

// splits input from an istream into tokens
std::vector <std::string> tokenize(std::istream &input) {
	char cur;
	std::string token = "";
	std::vector <std::string> tokens;

	std::string threeChar = "   ";
	int i = 0;
	
	while (input.get(cur)) {
	
		threeChar[i%3] = cur;
		if (isalnum(threeChar[i%3]) && threeChar[(i+2)%3]=='\'' 
			&& isalnum(threeChar[(i+1)%3])) {
			token = tokens[tokens.size()-2]+tokens[tokens.size()-1]+token;
			tokens.erase(tokens.end()-2, tokens.end());
		}
		i++;

		if (isalpha(cur) || isdigit(cur)) {
			token.push_back(cur);
		} else {
			if (token != "") {
				tokens.push_back(token);
				token = "";
			}
			if (!isspace(cur)) {
				tokens.push_back({cur});
			}
		}
	}
	if (token != "") {
		tokens.push_back(token);
	}
	return tokens;	
}

// counts syllables in a word
int countSyllables(std::string s) {
	if (s.size() == 0 || !isalpha(s[0])) {
		return 0;
	}
	if (s.size() == 1) {
		return 1;
	}
	int res = isVowel(s[0]), l = s.size() - 1;
	for (int i = 1; i < l; i++) {
		res += isVowel(s[i]) && !isVowel(s[i-1]);
	}
	res += isVowel(s[l]) && !isVowel(s[l-1]) && s[l] != 'e';

	return std::max(res, 1);
}

// evaluates an input stream
evaluationReport evaluateStream(std::istream &input) {

	evaluationReport res;
	std::vector <std::string> tokens = tokenize(input);
	
	for (std::string token : tokens) {
		if (isalpha(token[0])) {
			res.words++;
			res.syllables += countSyllables(token);
		}
		res.sentences += isSentenceBreak(token[0]);
	}
	
	res.words = std::max(res.words, 1);
	res.sentences = std::max(res.sentences, 1);
	res.grade = C[0] + C[1]*res.words/res.sentences + C[2]*res.syllables/res.words;

	return res;
}

// checks if file exists
bool fileExists(std::string filePath) {
	std::ifstream file(filePath);
	return file.good();
}

// checks if given character is a vowel
inline bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

// checks if given character ends a sentence
inline bool isSentenceBreak(char c) {
	return c == '.' || c == '?' || c == '!';
}

// evaluates a file
evaluationReport evf(std::string filePath) {

	evaluationReport res;
	
	if (fileExists(filePath)) {
		std::ifstream file;
		file.open(filePath);
		res = evaluateStream(file);
		file.close();
	} else {
		res.error_code = -1;		
	}
	res.filePath = filePath;
	
	return res;
}

// iterates input stream and processes each string in certain way
// this wasn't really necessary, just wanted to try out a bit of functional
// programming in C++
void iterateStream(std::istream &input, std::function <void(std::string)> process) {
	std::string str;
	while (input >> str) {
		process(str);
	}
}

// displays help message
inline void displayHelpMessage() {
	std::cout << "USAGE: FleschKincaid [OPTIONS]... [FILE]...\n";
	std::cout << "Evaluate grade level of text file(s).\n";
	std::cout << "\n";
	std::cout << "With no files read the standard input for file paths.\n";
	std::cout << "\n";
	std::cout << "\t-i, --input\t input files\n";
	std::cout << "\t-p, --pathFile\t evaluate files whose path is stored in the following files\n";
	std::cout << "\t-r, --raw\t evaluate text from standard input\n";
	std::cout << "\t-h, --help\t display help message\n";
	std::cout << "\n";
}

// displays report
void displayReport(evaluationReport report, bool detailed) {
	if (report.filePath != "") {
		std::cout << report.filePath << ": ";
	}
	if (report.error_code != 0) {
		std::cout << err_msg[report.error_code] << "\n";
	} else {
		if (detailed) {
			std::cout << "\n";
			std::cout << "Words: " << report.words << "\n";
			std::cout << "Sentences: " << report.sentences << "\n";
			std::cout << "Syllables: " << report.syllables << "\n";
			std::cout << "Grade: " << report.grade << "\n\n";
		} else {
			std::cout << report.grade << "\n";
		}
	}
}

