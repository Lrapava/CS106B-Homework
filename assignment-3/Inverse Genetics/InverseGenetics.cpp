/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(std::string protein, std::map<char, std::set<std::string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
std::map<char, std::set<std::string>> loadCodonMap();

int main() {
	/* Load the codon map. */
	std::map<char, std::set<std::string> > codons = loadCodonMap();
	std::string protein;
	
	while (getline(std::cin, protein)) {
		if (protein == "!exit") {
			return 0;
		}
		listAllRNAStrandsFor(protein, codons);
	}
	
	return 0;
}

std::vector <std::string> generateAllStringsFor(std::string &protein, std::map<char, std::set<std::string> >& codons) {
	
	std::vector <std::string> opt;
	for (std::string x : codons[protein[0]]) {
		opt.push_back(x);
	}

	if (protein.size() == 1) {
		return opt;
	}

	std::string sub = protein.substr(1);
	std::vector <std::string> subOpt = generateAllStringsFor(sub, codons);
	std::vector <std::string> res;

	for (std::string s : opt) {
		for (std::string q : subOpt) {
			res.push_back(s + q);
		}
	}

	return res;
	
}

void listAllRNAStrandsFor(std::string protein, std::map<char, std::set<std::string> >& codons) {
	std::vector <std::string> options = generateAllStringsFor(protein, codons);
	for (std::string s : options) {
		std::cout << s << "\n";
	}
}

/* You do not need to change this function. */
std::map<char, std::set<std::string> > loadCodonMap() {
	std::ifstream input("codons.txt");
	std::map<char, std::set<std::string>> result;

	/* The current codon / protein combination. */
	std::string codon;
	char protein;

	/* Continuously pull data from the file until all data has been read. */
	while (input >> codon >> protein) {
		result[protein].insert(codon);
	}

	return result;
}
