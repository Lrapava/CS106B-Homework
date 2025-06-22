#ifndef CMD_HPP
#define CMD_HPP

#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Command {
	public:
	Command(std::function <void(const std::vector <std::string>&)> f, int n, std::string desc) 
		:func(f), argc(n), description(desc) {}
	Command(std::function <void(const std::vector <std::string>&)> f, int n) 
		:func(f), argc(n) {}
	Command(std::function <void(const std::vector <std::string>&)> f, std::string desc) 
		:func(f), description(desc) {}
	Command(std::function <void(const std::vector <std::string>&)> f) 
		:func(f) {}
	Command() {};
	
	void execute(const std::vector <std::string>& args) {
		if ((int)args.size() != argc) {
			std::cerr << "Inappropriate number of arguments.\n";
		} else {
			func(args);
		}
	}
	std::string getDesc() {
		return description;
	}
	int getArgc() {
		return argc;
	}
	private:
	std::function <void(const std::vector <std::string>&)> func = [](const std::vector <std::string>& args){};
	int argc = 1;
	std::string description = "Undocumented function.";
};

extern std::map <std::string, Command> cmdLib;

void initCmdLib();

#endif
