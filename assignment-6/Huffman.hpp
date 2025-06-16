#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <unordered_map>
#include <iostream>
#include <istream>
#include <string>
#include <map>

#include "HuffmanTypes.hpp"
#include "bitio.hpp"


// Frequency table: maps characters to frequencies
std::unordered_map<ext_char, int> getFrequencyTable(const std::string& data);

// Build Huffman encoding tree from frequency table
Node* buildEncodingTree(const std::unordered_map<ext_char, int>& frequencies);

// Free memory used by the Huffman tree
void freeTree(Node* root);

// Encode file content into compressed bitstream
void encodeFile(const std::string& data, Node* encodingTree, BitWriter& writer);

// Decode bitstream using the Huffman tree
void decodeFile(std::istream& infile, Node* encodingTree, std::ostream& outfile);

// Complete compress: frequency table + tree + encoded bits
void compress(std::istream& infile, std::ostream& outfile);

// Complete decompress: read tree + decode bits
void decompress(std::istream& infile, std::ostream& outfile);

void serializeTree(Node* node, std::ostream& outfile);

// Reads stored conversion table from a file
Node* deserializeTreeHelper(BitReader& reader);

#endif
