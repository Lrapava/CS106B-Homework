#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Lexicon.hpp"

class Lexicon::lexiconUnit {
	public:
	lexiconUnit(char cc) :c(cc) {}

	char c;
	bool isWord = false;
	std::map <char, lexiconUnit*> nextLetters;

	private:
};

Lexicon::Lexicon() {
	root = new lexiconUnit('@');
}

Lexicon::Lexicon(std::string path) {
	std::ifstream file;
	file.open(path);
	
	if (file.is_open()) {
		root = new lexiconUnit('@');

		std::string s;
		while (getline(file, s)) {

			std::transform(s.begin(), s.end(), s.begin(), 
				[](unsigned char c) { return std::tolower(c); }
			);

			longestWordLength = std::max(longestWordLength, (int)s.size());
			
			lexiconUnit* cur = root;
			for (int i = 0, l = s.size(); i < l; i++) {
				if (cur->nextLetters.find(s[i]) == cur->nextLetters.end()) {
					cur->nextLetters[s[i]] = new lexiconUnit(s[i]);
				}
				cur = cur->nextLetters[s[i]];
			}
			cur->isWord = true;
		}
	} else {
		std::cerr << "Failed to open lexicon.\n";
	}

	file.close();
}

bool Lexicon::contains(std::string word) const {
	lexiconUnit* cur = root;
	for (int i = 0, l = word.size(); i < l; i++) {
		if (cur->nextLetters.find(word[i]) == cur->nextLetters.end()) {
			return false;
		}
		cur = cur->nextLetters[word[i]];
	}
	return cur->isWord;
}

bool Lexicon::containsPrefix(std::string pfx) const {
	lexiconUnit* cur = root;
	for (int i = 0, l = pfx.size(); i < l; i++) {
		if (cur->nextLetters.find(pfx[i]) == cur->nextLetters.end()) {
			return false;
		}
		cur = cur->nextLetters[pfx[i]];
	}
	return true;
}

int Lexicon::getLongestWordLength() const {
	return longestWordLength;
}

Lexicon::~Lexicon() {
	deleteSubtree(root);
}

void Lexicon::deleteSubtree(lexiconUnit* node) {
	for (auto& pair : node->nextLetters) {
		deleteSubtree(pair.second);
	}
	delete node;
}
