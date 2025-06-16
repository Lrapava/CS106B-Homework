#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include <map>
#include <mutex>

#include "Lexicon.hpp"

const std::string STANDARD_CUBES[16] = {
		"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
		"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
		"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
		"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
	};

const int BOARD_SIZE = 4;
const int BOARD_AREA = BOARD_SIZE * BOARD_SIZE;
const int CUBE_FACES = 6;
const int MIN_WORD_LENGTH = 4;

class BoggleBoard {

public:

	char** board;

	BoggleBoard();
	BoggleBoard(const Lexicon& lexi);
	~BoggleBoard();

	void display();
	void display(std::unordered_set <short> highlight);
	void highlightWord(std::string word);

	std::unordered_set <short> getHighlight(std::string word);
	std::unordered_set <std::string> getValidWords();

	int getWordCount();
	int getMaxScore();
	bool wordIsValid(std::string word);


private:

	void tryPosition(short pos, std::unordered_set <short>& was, std::string& word, std::unordered_set<std::string>& valid);
	void findEverything();
	
	std::unordered_set <std::string> allValidWords;
	std::map <std::string, std::unordered_set <short>> highlights;
	
	int humanScore = 0;
	int maxScore = 0;
	std::mutex highlight_mutex;
	const Lexicon& lex;
};

#endif
