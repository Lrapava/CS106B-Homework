#ifndef LEXICON_H
#define LEXICON_H

#include <map>
#include <string>

class Lexicon {
public:
	Lexicon();
	Lexicon(std::string path);
	
	bool contains(std::string word) const;
	bool containsPrefix(std::string pfx) const;
	int getLongestWordLength() const;

	Lexicon(const Lexicon&) = delete;
	Lexicon& operator=(const Lexicon&) = delete;
	
	~Lexicon();

private:

	class lexiconUnit;

	int longestWordLength = 0;
	void deleteSubtree(lexiconUnit* node);
	lexiconUnit* root;

};

#endif
