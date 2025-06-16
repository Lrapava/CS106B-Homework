/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <type_traits>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <string>
#include <map>

std::map <std::string, std::vector <std::string>> processArgs(int &argn, char* argv[], std::map <std::string, std::string> altarg);
bool fileExists(const std::string &filename);
void helpMessage();

void train();
void generate();
void compare();

// checks if a file exists
std::map <std::string, std::string> altarg = {
	{ "--help",				"-h" },
	{ "--input",			"-i" },
	{ "--order",			"-r" },
	{ "--output",			"-o" },
	{ "--length",			"-l" },
	{ "--words-mode",		"-w" },
	{ "--char-mode",		"-c" },
};

std::map <std::string, std::vector <std::string>> argm;

std::map <std::string, std::function <void()>> validCommands = {
	{ "train",		train },
	{ "generate",	generate },
	{ "compare",	compare },
};

// model described in problem statement
template <class T>
class markovModel {
public:

	// markovModel(std::string path) {
		// importModel(path);
	// }
	
	markovModel(int order) {
		this->order = order;
	}

	markovModel(int order, std::istream &input) {
		this->order = order;
		train(input);
	}

	std::string stringify() {
		std::string res = "";
		if (std::is_same<T, char>::value) {
			res = "c\n";
		} else {
			res = "s\n";
		}
		res += std::to_string(order);
		res += std::to_string(total);

		return res;
	}


	void destringify(std::string str) {
		std::istringstream iss(str);
		destringify(iss);
	}

	void destringify(std::istream input) {
		char c;
		input >> c;
		if (c == 'c' && std::is_same<std::string, T>::value || c == 's' && std::is_same<char, T>::value) {
			error_code = 2;
			return;
		}
		input >> order;
		input >> total;
		for (std::pair <std::vector <T>, entry> p : data) {
			
		} 
	}
	
	// train from an input stream
	void train(std::istream &input) {

		T ch;
		std::vector <T> window;
		
		while ((int)window.size() < order) {
			if (input >> ch) {
				window.push_back(ch);
			} else {
				err = 1;
				return;
			}
		}

		while (input >> ch) {
			total++;
			data[window].total++;
			data[window].Tf[ch]++;
			window.push_back(ch);
			window = window.substr(1);
		}

		int maxf = 0;
		for (std::pair <std::vector <T>, entry> p : data) {
			if (p.second.total > maxf) {
				maxf = p.second.total;
				mode_seed = p.first;
			}
		}

	}

	// n Tacter long string
	std::vector <T> generate(int length) {

		int n = length - order;
		int random = rand() % total;
		std::vector <T> text = mode_seed;

		#ifdef RANDOM_SEED
			for (std::pair <std::vector <T>, entry> p : data) {
				random -= p.second.total;
				if (random <= 0) {
					text = p.first;
					break;
				}
			}
		#endif

		for (int i = 0; i < n; i++) {
			std::vector <T> window(text.end() - order, text.end());
			random = rand() % data[window].total;
			T res;
			for (std::pair <T, int> p : data[window].Tf) {
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

	struct entry {
		int total = 0;
		std::map <T, int> Tf;
	};

	int order;
	int total = 0;
	std::vector <T> mode_seed;
	std::map <std::vector<T>, entry> data;
		
	int err = 0;
		
};

int main(int argn, char* argv[]) {

	for (std::pair <std::string, std::string> p : altarg) {
		if (p.first[1] == '-') {
			altarg[p.second] = altarg[p.first];
		}
	}

	argm = processArgs(argn, argv, altarg);

	if (argm.find("-h") != argm.end()) {
		helpMessage();
		return 0;
	}

	if (argm[""].size() < 1 || validCommands.find(argm[""][0]) == validCommands.end()) {
		std::cerr << "Invalid command!\nUse \"RandomWriter -h\" for help.\n";
		return 1;
	}
	
	if (argm.find("error")!= argm.end()) {
		for (std::string error : argm["error"]) {
			std::cerr << error;
		}
		return 1;
	}

	validCommands[argm[""][0]]();
	
}

std::map <std::string, std::vector <std::string>> processArgs(int &argn, char* argv[], std::map <std::string, std::string> altarg) {

	std::map <std::string, std::vector <std::string>> argm;
	
	std::string activeFlag = "";
	for (int i = 1; i < argn; i++) {
		std::string arg(argv[i]);
		if (arg[0] == '-') {
			activeFlag = arg;
			if (altarg.find(arg) != altarg.end()) {
				if (activeFlag[1] == '-') {
					activeFlag = altarg[activeFlag];
				}
				argm[activeFlag].push_back("");
			} else {
				argm["error"].push_back("Invalid flag \"" + activeFlag + "\".\n");
			}
		} else {
			argm[activeFlag].push_back(arg);
		}
	}
	
	return argm;
	
}

void train() {
	if (argm[""].size() != 2) {
		std::cerr << "You should provide exactly one model to train.\n";
	}

}

void generate() {
	
}

void compare() {
	
}

bool fileExists(const std::string &filename) {
	std::ifstream file(filename);
	return file.good();
}

void helpMessage() {
	std::cout << "USAGE: RandomWriter [COMMAND] [MODEL].. [OPTIONS]..\n";
	std::cout << "\n";
	std::cout << "Available commands:\n";
	std::cout << "train \t\t trains/retrains a model\n";
	std::cout << "generate \t used for generating text from model\n";
	std::cout << "compare \t used for comparing two models\n";
}
