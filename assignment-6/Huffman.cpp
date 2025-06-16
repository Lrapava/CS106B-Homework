#include <unordered_map>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <queue>
#include <set>
#include <map>

#include "HuffmanTypes.hpp"
#include "Huffman.hpp"
#include "bitio.hpp"

void freeTree(Node* root) {
	if (root == NULL) {
		return;
	}
	freeTree(root->zero);
	freeTree(root->one);
	delete root;
}


void compress(std::istream& infile, std::ostream& outfile) {
	std::string data((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

	std::unordered_map<ext_char, int> freqTable = getFrequencyTable(data);
	Node* encodingTreeRoot = buildEncodingTree(freqTable);

	serializeTree(encodingTreeRoot, outfile);
	BitWriter writer(static_cast<std::ofstream&>(outfile));
	encodeFile(data, encodingTreeRoot, writer);

	writer.flush();
	freeTree(encodingTreeRoot);
}

std::unordered_map<ext_char, int> getFrequencyTable(const std::string& data) {
	std::unordered_map<ext_char, int> table;
	for (char c : data) {
		ext_char cext = static_cast<ext_char>(static_cast<unsigned char>(c));
		table[cext]++;
	}
	table[PSEUDO_EOF] = 1;
	return table;
}

Node* buildEncodingTree(const std::unordered_map<ext_char, int>& frequencies) {

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;

    for (const auto& pair : frequencies) {
        if (pair.second > 0) {
            pq.push(new Node(pair.first, pair.second));
        }
    }
    
	pq.push(new Node(PSEUDO_EOF, 1));

	while (pq.size() > 1) {
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top(); pq.pop();

		Node* parent = new Node(left, right);
		parent->character = NOT_A_CHAR;

		pq.push(parent);
	}

	if (pq.empty()) {
		return nullptr;
	}

	return pq.top();
}

void serializeTreeHelper(Node* node, BitWriter& writer) {
	if (node == NULL) {
		return;
	}
	if (node->zero == nullptr && node->one == nullptr) {
		// leaf
		writer.writeBit(1);  
		unsigned int ch = static_cast<unsigned int>(node->character);
		for (int i = 8; i >= 0; i--) {
			bool bit = (ch >> i) & 1;
			writer.writeBit(bit);
		}
	} else {
		// internal node
		writer.writeBit(0);
		serializeTreeHelper(node->zero, writer);
		serializeTreeHelper(node->one, writer);
	}
}

void serializeTree(Node* node, std::ostream& outfile) {
	BitWriter writer(outfile);
	serializeTreeHelper(node, writer);
	writer.flush();
}

Node* deserializeTreeHelper(BitReader& reader) {
	bool bit = reader.readBit();
	if (bit) {
		// Leaf node: next 9 bits encode the character
		ext_char ch = 0;
		for (int i = 0; i < 9; i++) {
			ch <<= 1;
			ch |= reader.readBit() ? 1 : 0;
		}
		return new Node(ch, 0); // weight can be 0 here
	} else {
		// Internal node
		Node* left = deserializeTreeHelper(reader);
		Node* right = deserializeTreeHelper(reader);
		Node* parent = new Node(left, right);
		parent->character = NOT_A_CHAR;
		return parent;
	}
}

Node* deserializeTree(std::istream& infile) {
	BitReader reader(infile);
	return deserializeTreeHelper(reader);
}

void buildEncodingMap(Node* node, const std::string& path, std::unordered_map<ext_char, std::string>& encodingMap) {
	if (node == NULL) {
		return;
	}

	if (node->zero == nullptr && node->one == nullptr) {
		encodingMap[node->character] = path;
		return;
	}

	buildEncodingMap(node->zero, path + "0", encodingMap);
	buildEncodingMap(node->one,  path + "1", encodingMap);
}

void encodeFile(const std::string& data, Node* encodingTree, BitWriter& writer) {
	std::unordered_map<ext_char, std::string> encodingMap;
	buildEncodingMap(encodingTree, "", encodingMap);

	// write data
	for (char c : data) {
		ext_char ch = static_cast<ext_char>(static_cast<unsigned char>(c));
		const std::string& bits = encodingMap[ch];
		for (char bitChar : bits) {
			writer.writeBit(bitChar == '1');
		}
	}

	// write PSEUDO_EOF
	const std::string& eofBits = encodingMap[PSEUDO_EOF];
	for (char bitChar : eofBits) {
		writer.writeBit(bitChar == '1');
	}
}

void decompress(std::istream& infile, std::ostream& outfile) {

	Node* root = deserializeTree(infile);

	BitReader reader(infile);
	Node* current = root;

	while (true) {
		bool bit = reader.readBit();

		current = bit ? current->one : current->zero;

		if (!current->zero && !current->one) {
			if (current->character == PSEUDO_EOF) {
				break;
			}
			outfile.put(static_cast<char>(current->character));
			current = root;
		}
	}

	freeTree(root);
}
