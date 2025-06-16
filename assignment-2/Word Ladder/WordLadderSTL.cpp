/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

// I have put some effort into getting the Stanford library to work on Linux, including selecting some
// specific files (lexicon.h, lexicon.cpp, etx) for compilation, compiling the library from source
// code using provided instruction but to no avail, got some compilation errors after running make.
// I am not willing to debug the library or generate instructions to get it to work on Linux, 
// since I do not see it as my responsibility considering the fact that Linux is not as uncommon 
// nowadays - ~5% of personal computers are running Linux with the number growing every year, ~9% of
// second year physics students using it (matching the share of Mac users), nor as a particularly
// productive investment of my time.

// For testing purposes, I will implement a similar class and call it a day.

// Alternative for lexicon.h since I couldn't get the library to run on Linux.
class Lexicon {
public:
	Lexicon() {}
	Lexicon(std::string path) {
		std::fstream file;
		file.open(path);
		if (file.is_open()) {
			std::string s;
			while (getline(file, s)) {
				dict.insert(s);
			}
		}
	}
	bool contains(std::string word) {
		return dict.find(word) != dict.end();
	}
private:
	std::set <std::string> dict;
};

// hamming-distance-like function
int dist(std::string a, std::string b);
// generates word ladder
std::vector <std::string> findLadder(std::string &start, std::string &end, Lexicon &lex);
// uses getline to input string until it satisfies isValid
std::string gateKeepInput(std::string prompt, std::function <bool(std::string)> isValid);

int main() {

	// using this text file since there was an issue getting the Stanford library to work
	// one could replace this line with Lexicon lex("EnglishWords.dat"); and add #include <lexicon.h>
	// above, but I failed to test that code, so I created my own lexicon. If this is a big issue,
	// please try implementing the changes described in this paragraph and running the code.
	Lexicon lex("20k.txt");
	
	std::string start, end;
	
	while (true) {

		start = gateKeepInput("Enter start word (RETURN to quit): ", [&lex](std::string s)->bool {
			return s == "" || lex.contains(s);
		});
		if (start == "") { 
			return 0; 
		}
		end = gateKeepInput("Enter destination word: ", [&lex](std::string s)->bool {
			return lex.contains(s);
		});
		
		if (start == end) {
			std::cout << "Start string matches end string.\n";
		} else {
			if (start.size() != end.size()) {
				std::cout << "Strings should be of the same length.\n";
			} else {
				std::vector <std::string> lad = findLadder(start, end, lex);
				if (lad.size() > 1) {
					for (std::string s : lad) {
						std::cout << s << " ";
					}
					std::cout << "\n";			
				} else {
					std::cout << "Ladder cannot be built.\n";
				}
			}
		}
		
	}
}

// hamming-distance-like function 
int dist(std::string a, std::string b) {
	if (a.size() > b.size()) {
		swap(a, b);
	}
	int res = b.size() - a.size();
	for (int i = 0, l = a.size(); i < l; i++) {
		res += (a[i] != b[i]);
	}
	return res;
}

// generates word ladder
std::vector <std::string> findLadder(std::string &start, std::string &end, Lexicon &lex) {

	std::priority_queue <std::pair <int, std::string>> q;
	std::map <std::string, std::string> prev;

	prev[start] = "";
	q.push({dist(start, end), start});

	while (!q.empty() && q.top().first != 0) {
		std::pair <int, std::string> p = q.top();
				
		for (int i = 0, l = p.second.size(); i < l; i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				if (c != p.second[i]) {
					std::string opt = p.second; 
					opt[i] = c;
					if (prev.find(opt) == prev.end() && lex.contains(opt)) {
						prev[opt] = p.second;
						int d = dist(opt, end);
						q.push({d, opt});
					}
				}
			}
		}
		q.pop();
	}

	std::string str = end;
	std::vector <std::string> res;

	while (str != "") {
		res.push_back(str);
		str = prev[str];
	}

	std::reverse(res.begin(), res.end());
	return res;
}

// uses getline to input string until it satisfies isValid
std::string gateKeepInput(std::string prompt, std::function <bool(std::string)> isValid) {
	std::string res;
	bool wasOnce = false;

	while (!wasOnce || !isValid(res)) {
		if (wasOnce) {
			std::cout << "Invlid word. Please try again.\n";
		}
		std::cout << prompt;
		getline(std::cin, res);
		wasOnce = true;		
	}
	
	return res;
}
