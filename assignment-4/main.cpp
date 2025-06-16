#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>

#include "Lexicon.hpp"
#include "BoggleBoard.hpp"

bool replayDialogue() {
	std::cout << "\nWant to play again? (y/n)\n";
	char c;
	do {
		std::cin >> c;
		std::cin.ignore(10000, '\n'); // flush until newline
	} while (c != 'y' && c != 'n');
	return c == 'y';
}

int main() {
	std::srand(std::time(nullptr));
	Lexicon lex20k("20k.txt");
	BoggleBoard* myBoard;

	bool gameRunning = true;
	while (gameRunning) {
	
	
		myBoard = new BoggleBoard(lex20k);

		myBoard->display();
		
		std::cout << "Player's turn. (Enter '!' once you give up)\n"; 
		std::cout << myBoard->getWordCount() << " words in total\n";

		std::unordered_set <std::string> humanWords;
		std::string humanWord;
		int playerScore = 0;

		while (true) {
			std::cout << "Enter word: ";
			std::cin >> humanWord;
			if (humanWord == "!") {
				break;
			}

			std::transform(humanWord.begin(), humanWord.end(), humanWord.begin(), 
				[](unsigned char c) { return std::tolower(c); }
			);

			if (humanWord.size() < MIN_WORD_LENGTH) {
				std::cout << "Word too short!\n";
			} else if (!lex20k.contains(humanWord)) {
				std::cout << "Word not found in the lexicon.\n";
			} else if (!myBoard->wordIsValid(humanWord)) {
				std::cout << "Word cannot be found on the board.\n";
			} else if (humanWords.find(humanWord) != humanWords.end()) {
				std::cout << "Word already found before.\n";
			} else {
				humanWords.insert(humanWord);
				playerScore += (int)humanWord.size() - MIN_WORD_LENGTH + 1;
				std::cout << "Words found: " << humanWords.size() << "; Score: " << playerScore << "\n";
				myBoard->highlightWord(humanWord);
			}
			
		}

		std::cout << "Words you found:\n";
		for (std::string word : humanWords) {
			std::cout << word << "\n";
		}
		std::cout << "\n";

		std::cout << "Words you missed:\n";
		std::unordered_set <std::string> wrds = myBoard->getValidWords();
		for (std::string word : wrds) {
			if (humanWords.find(word) == humanWords.end()) {
				std::cout << word << "\n";
			}
		}

		std::cout << "HUMAN: " << playerScore << "; COMPUTER " << myBoard->getMaxScore() - playerScore << "\n";
		delete myBoard;
		gameRunning = replayDialogue();
		
	}

	std::cout << "bye!\n";
}
