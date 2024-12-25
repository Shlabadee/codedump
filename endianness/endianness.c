#include <stdbool.h>
#include <stdint.h>

#include "endianness.h"

void tobigend64(uint8_t* buffer, uint64_t n)
{
	for (unsigned int i = 0, k = sizeof(n) - 1; i < sizeof(n); ++i)
	{
		buffer[k] = (uint8_t)n;
		n >>= 8;
		--k;
	}
}

void tobigend32(uint8_t* buffer, uint32_t n)
{
	for (unsigned int i = 0, k = sizeof(n) - 1; i < sizeof(n); ++i)
	{
		buffer[k] = (uint8_t)n;
		n >>= 8;
		--k;
	}
}

void tobigend16(uint8_t* buffer, uint16_t n)
{
	for (unsigned int i = 0, k = sizeof(n) - 1; i < sizeof(n); ++i)
	{
		buffer[k] = (uint8_t)n;
		n >>= 8;
		--k;
	}
}

void tolitend32(uint8_t* buffer, uint32_t n)
{
	for (unsigned int i = 0; i < sizeof(n); ++i)
	{
		buffer[i] = (uint8_t)n;
		n >>= 8;
	}
}

void tolitend16(uint8_t* buffer, uint16_t n)
{
	for (unsigned int i = 0; i < sizeof(n); ++i)
	{
		buffer[i] = (uint8_t)n;
		n >>= 8;
	}
}

uint32_t fromlitend32(uint8_t* buffer)
{
	uint32_t n = 0;
	for (unsigned int i = 0; i < sizeof(n); ++i)
	{
		n |= (uint32_t)buffer[i] << (8 * i);
	}

	return n;
}

uint32_t frombigend32(uint8_t* buffer)
{
	uint32_t n = 0;
	for (unsigned int i = 0, k = sizeof(n) - 1; i < sizeof(n); ++i)
	{
		n |= (uint32_t)buffer[i] << (8 * k);
		--k;
	}

	return n;
}

uint16_t fromlitend16(uint8_t* buffer)
{
	uint16_t n = 0;
	for (unsigned int i = 0; i < sizeof(n); ++i)
	{
		n |= (uint16_t)buffer[i] << (8 * i);
	}

	return n;
}

uint16_t frombigend16(uint8_t* buffer)
{
	uint16_t n = 0;
	for (unsigned int i = 0, k = sizeof(n) - 1; i < sizeof(n); ++i)
	{
		n |= (uint16_t)buffer[i] << (8 * k);
		--k;
	}

	return n;
}
