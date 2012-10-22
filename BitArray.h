#pragma once

#include <iostream>

using std::string;

class BitArray
{
public:
	// Definition: create a bit array 8 bits long, all the bits set to 0
	BitArray();

	// Definition: create a bit array of bufferLen bytes in buffer
	BitArray(unsigned char *buffer, size_t bufferLen);

	~BitArray(void);

	
	// Definition: get the value of a bit at bitIndex in the array
	bool BitAt(int bitIndex);

	// Definition: set the bit at bitIndex
	void SetBit(int bitIndex);

	// Definition: clear the bit at bitIndex
	void ClearBit(int bitIndex);

	// Definition: set all the bits in the array
	void SetAll();

	// Definition: clear all the bits in the array
	void ClearAll();

private:
	unsigned char *buffer;
	size_t bufferLen;
	bool bufferInternAllocation;
};

