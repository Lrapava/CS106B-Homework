#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "State.hpp"
#include "Alg.hpp"
#include "Cmd.hpp"

std::vector <std::string> tokenize(const std::string& cmd) {
	std::vector <std::string> res;
	std::stringstream ss(cmd);
	std::string token;
	while (ss >> token) {
		res.push_back(token);
	}
	return res;
}

int main() {

	State::reset();
	initCmdLib();
	initAlgLib();

	std::cout << "Welcome to trailblazer.\n";
	std::cout << "Type `help` for help\n";
	std::string cmd = "";
	
	while (State::isRunning && getline(std::cin, cmd)) {
		auto tk = tokenize(cmd);

		if (tk.size() == 0) {
			continue;
		}
		
		if (cmdLib.find(tk[0]) != cmdLib.end()) {
			cmdLib[tk[0]].execute(tk);
		} else {
			std::cerr << "Command not found.\n";
		}
	}
}
