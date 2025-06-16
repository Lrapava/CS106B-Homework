#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include <mutex>
#include <map>

#include "Lexicon.hpp"
#include "BoggleBoard.hpp"

BoggleBoard::BoggleBoard(const Lexicon& lexi):lex(lexi) {
	
	board = new char*[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = new char[BOARD_SIZE];
	};

	bool used[BOARD_AREA];
	for (int i = 0; i < BOARD_AREA; i++) {
		used[i] = false;
	}
	int chosen = 0;
	int sequence[BOARD_AREA];
	
	while (chosen < BOARD_AREA) {
		int choice = rand() % BOARD_AREA;
		if (!used[choice]) {
			used[choice] = true;
			sequence[chosen] = choice;
			chosen++;
		}
	}

	for (int i = 0; i < BOARD_AREA; i++) {
		board[i/BOARD_SIZE][i%BOARD_SIZE] = STANDARD_CUBES[sequence[i]][rand()%CUBE_FACES];
	}

	findEverything();
}

void BoggleBoard::display(std::unordered_set <short> highlight) {
	std::cout << "-----------------\n";
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << "|";
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (highlight.find(BOARD_SIZE*i+j) != highlight.end()) {
				std::cout << "[" << board[i][j] << "]|";
			} else {
				std::cout << " " << board[i][j] << " |";
			}
		}
		std::cout << "\n-----------------\n";
	}
}


void BoggleBoard::display() {
	display({});
}

BoggleBoard::~BoggleBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;
}

std::unordered_set <short> BoggleBoard::getHighlight(std::string word) {
	if (highlights.find(word) == highlights.end()) {
		return {};
	}
	return highlights[word];
}

void BoggleBoard::highlightWord(std::string word) {
	display(getHighlight(word));
}

int BoggleBoard::getWordCount() {
	return allValidWords.size();
}

std::unordered_set <std::string> BoggleBoard::getValidWords() {
	return allValidWords;
}

int BoggleBoard::getMaxScore() {
	return maxScore;
}

bool BoggleBoard::wordIsValid(std::string word) {
	std::cout << "Looking for: " << word << "\n";
	return allValidWords.find(word) != allValidWords.end();
}

void BoggleBoard::tryPosition(short pos, std::unordered_set <short>& was, std::string& word, std::unordered_set<std::string>& valid) {
	if (lex.containsPrefix(word) && was.find(pos) == was.end()) {
		was.insert(pos);
		word.push_back(board[pos/BOARD_SIZE][pos%BOARD_SIZE]-'A'+'a');
		
		{
			if (word.size() >= MIN_WORD_LENGTH && lex.contains(word)) {
				valid.insert(word);
				std::lock_guard<std::mutex> lock(highlight_mutex);
				highlights[word] = was;
			}
		}
		
		short x = pos / BOARD_SIZE, y = pos % BOARD_SIZE;
		
		for (short i = -1; i < 2; i++) {
			for (short j = -1; j < 2; j++) {
				short tx = x + i, ty = y + j;
				if (tx >= 0 && tx < BOARD_SIZE && ty >= 0 && ty < BOARD_SIZE && (i != 0 || j != 0)) {
					tryPosition((tx * BOARD_SIZE) + ty, was, word, valid);
				}
			}
		}
		word.pop_back();
		was.erase(pos);
	}
}

void BoggleBoard::findEverything() {

	std::vector <std::unordered_set<short>> wasVec(BOARD_AREA);
	std::vector <std::unordered_set <std::string>> validVec(BOARD_AREA);
	std::vector <std::string> stringVec(BOARD_AREA);
	std::vector <std::thread> threadVec;

	for (int i = 0; i < BOARD_AREA; i++) {
		threadVec.emplace_back([=, &wasVec, &stringVec, &validVec, this](int index) {
		    this->tryPosition(index, wasVec[index], stringVec[index], validVec[index]);
		}, i);
	}

	for (int i = 0; i < BOARD_AREA; i++) {
		threadVec[i].join();
		for (std::string word : validVec[i]) {
			allValidWords.insert(word);
			maxScore += (int)(word.size()) - MIN_WORD_LENGTH + 1;
		}
	}
}

