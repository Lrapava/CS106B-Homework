#include <unordered_map>
#include <iostream>
#include <istream>
#include <thread>
#include <string>
#include <vector>
#include <map>

#include "HuffmanTypes.hpp"
#include "Huffman.hpp"
#include "bitio.hpp"

int main(int argc, char** argv) {

	std::string inputFileLocation, outputFileLocation;
	std::map <std::string, std::vector <std::string>> opt;

	{
		std::string curOpt = "";
		for (int i = 0; i < argc; i++) {
			if (argv[i][0] == '-') {
				curOpt = std::string(argv[i]);
			} else {
				opt[curOpt].push_back(std::string(argv[i]));
			}
		}
	}

	if (opt["-x"].size() + opt["-c"].size() == 0 || opt["-c"].size()*opt["-x"].size() != 0) {
		std::cout << "Welcome to Huffman encoding user manual\n\n";
		std::cout << argv[0] << " <MODE> <INPUT_FILES> -o <OUTPUT_FILES>\n";
		std::cout << argv[0] << " <MODE> <INPUT_FILES>\n\n";
		std::cout << "For mode use `-x` to extract or `-c` to compress.\n";
		std::cout << "If ommit `-o <OUTPUT_FILES>`, names will be generate automatically.\n";
		std::cout << "When using `-o`, provide appropriate number of file paths.\n";
		std::cout << "You may use only one mode at a time.\n";
		return 0;
	}

	std::vector<std::thread> threads;
	
	for (int i = 0, l = opt["-x"].size(); i < l; i++) {
		threads.emplace_back([i, &opt]() {
			std::ifstream infile(opt["-x"][i], std::ios::binary);
			if (!infile) {
				std::cerr << "Failed to open input file: " << opt["-x"][i] << "\n";
				return;
			}

			std::string outFilePath = opt["-x"][i] + ".dehuff";
			if (i < (int)opt["-o"].size()) {
				outFilePath = opt["-o"][i];
			}

			std::ofstream outfile(outFilePath, std::ios::binary);
			if (!outfile) {
				std::cerr << "Failed to open output file: " << outFilePath << "\n";
				return;
			}

			decompress(infile, outfile);

		});
	}

	for (int i = 0, l = opt["-c"].size(); i < l; i++) {
		threads.emplace_back([i, &opt]() {
			std::ifstream infile(opt["-c"][i], std::ios::binary);
			if (!infile) {
				std::cerr << "Failed to open input file: " << opt["-c"][i] << "\n";
				return;
			}

			std::string outFilePath = opt["-c"][i] + ".huff";
			if (i < (int)opt["-o"].size()) {
				outFilePath = opt["-o"][i];
			}

			std::ofstream outfile(outFilePath, std::ios::binary);
			if (!outfile) {
				std::cerr << "Failed to open output file: " << outFilePath << "\n";
				return;
			}

			compress(infile, outfile);

		});
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

}
