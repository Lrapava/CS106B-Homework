#ifndef BITIO_HPP
#define BITIO_HPP

#include <fstream>
#include <cstdint>

class BitWriter {
	std::ostream& out;
	uint8_t buffer = 0;
	int bitsFilled = 0;

public:
	BitWriter(std::ostream& o) : out(o) {}

	void writeBit(int bit) {
		buffer = (buffer << 1) | (bit & 1);
		bitsFilled++;

		if (bitsFilled == 8) {
			out.put(buffer);
			buffer = 0;
			bitsFilled = 0;
		}
	}

	void flush() {
		if (bitsFilled > 0) {
			buffer <<= (8 - bitsFilled); // pad with 0s
			out.put(buffer);
			buffer = 0;
			bitsFilled = 0;
		}
	}
};


class BitReader {
	std::istream& in;
	uint8_t buffer = 0;
	int bitsLeft = 0;

public:
	BitReader(std::istream& i) : in(i) {}

	int readBit() {
		if (bitsLeft == 0) {
			int byte = in.get();
			if (byte == EOF) throw std::runtime_error("Unexpected EOF");
			buffer = static_cast<uint8_t>(byte);
			bitsLeft = 8;
		}
		int bit = (buffer >> (bitsLeft - 1)) & 1;
		bitsLeft--;
		return bit;
	}
};

#endif
