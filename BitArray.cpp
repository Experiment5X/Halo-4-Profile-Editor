#include "BitArray.h"
#include <string.h>

BitArray::BitArray() :
	bufferInternAllocation(true), bufferLen(1)
{
	buffer = new unsigned char;
	*buffer = 0;
}

BitArray::BitArray(unsigned char *buffer, size_t bufferLen) :
	bufferInternAllocation(false), buffer(buffer), bufferLen(bufferLen)
{

}

BitArray::~BitArray()
{
	if (bufferInternAllocation)
		delete buffer;
}

bool BitArray::BitAt(int bitIndex)
{
	if (bitIndex < 0 || bitIndex > (bufferLen * 8))
		throw string("BitArray: Index outside the bounds of the array.\n");

	return !!(buffer[bitIndex >> 3] & (0x80 >> (bitIndex & 7)));
}

void BitArray::SetBit(int bitIndex)
{
	if (bitIndex < 0 || bitIndex > (bufferLen * 8))
		throw string("BitArray: Index outside the bounds of the array.\n");

	buffer[bitIndex >> 3] |= (0x80 >> (bitIndex & 7));
}

void BitArray::ClearBit(int bitIndex)
{
	if (bitIndex < 0 || bitIndex > (bufferLen * 8))
		throw string("BitArray: Index outside the bounds of the array.\n");

	buffer[bitIndex >> 3] &= ~(0x80 >> (bitIndex & 7));
}

void BitArray::SetAll()
{
	memset(buffer, 0xFF, bufferLen);
}

void BitArray::ClearAll()
{
	memset(buffer, 0, bufferLen);
}
