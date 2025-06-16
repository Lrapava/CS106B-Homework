/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <functional>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <map>

#define CHAR_NUM 2000

// checks if a file exists
bool fileExists(const std::string &filename) {
	std::ifstream file(filename);
	return file.good();
}

// safely input some type
template <typename T>
T safeInput() {
	T value;
	std::cin >> value;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid value." << std::endl;
		std::cin >> value;
	}
	return value;
}

// prompt user to input some typename till some criteria is met
template <typename T>
T gateKeeper(std::string prompt, std::function <bool(T)> isValid) {
	T input;
	std::cout << prompt;
	std::cin >> input;
	while (!isValid(input)) {
		std::cout << "Invalid input. Please try again.\n";
		std::cout << prompt;
		input = safeInput<T>();
	}
	return input;
}

// model described in problem statement
class markovModel {
public:

	markovModel(int order) {
		this->order = order;
	}

	markovModel(int order, std::istream &input) {
		this->order = order;
		train(input);
	}

	// train from an input stream
	void train(std::istream &input) {

		char ch;
		std::string window;
		
		while ((int)window.size() < order) {
			if (input.get(ch)) {
				window.push_back(ch);
			} else {
				err = 1;
				return;
			}
		}

		while (input.get(ch)) {
			total++;
			data[window].total++;
			data[window].charf[ch]++;
			window.push_back(ch);
			window = window.substr(1);
		}

		int maxf = 0;
		for (std::pair <std::string, entry> p : data) {
			if (p.second.total > maxf) {
				maxf = p.second.total;
				mode_seed = p.first;
			}
		}

	}

	// n character long string
	std::string generate(int length) {

		int n = length - order;
		int random = rand() % total;
		std::string text = mode_seed;

		#ifdef RANDOM_SEED
			for (std::pair <std::string, entry> p : data) {
				random -= p.second.total;
				if (random <= 0) {
					text = p.first;
					break;
				}
			}
		#endif

		for (int i = 0; i < n; i++) {
			std::string window = text.substr(text.size() - order, order);
			random = rand() % data[window].total;
			char res;
			for (std::pair <char, int> p : data[window].charf) {
				random -= p.second;
				if (random <= 0) {
					res = p.first;
					break;
				}
			}
			text.push_back(res);
		}
		
		return text;
	}

	int error_code() {
		return err;
	}
	
private:

	int order;
	int err = 0;
	int total = 0;
	
	std::string mode_seed = "";
	
	struct entry {
		int total = 0;
		std::map <char, int> charf;
	};

	std::map <std::string, entry> data;
	
};

int main() {

	srand(time(NULL));

	std::string filePath = gateKeeper<std::string>("Enter soure file:\n", fileExists);
	int order = gateKeeper<int>("Enter model order [1-10]: ", [](int x)->bool { return x > 0 && x < 11; } );

	std::ifstream file(filePath);

	if (!file) {
	    std::cerr << "Error opening file!" << std::endl;
	    return 1;
	}

	markovModel model(order, file);

	if (model.error_code()) {
		std::cerr << "Error generating model!" << std::endl;
	    return model.error_code();
	}
	
	std::string output = model.generate(CHAR_NUM);

	if (model.error_code()) {
		std::cerr << "Error generating output!" << std::endl;
	    return model.error_code();
	}

	std::cout << output << std::endl;
}
