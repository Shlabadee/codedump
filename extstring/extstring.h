#ifndef EXTSTRING_H
#define EXTSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

static void wordset(uint16_t* restrict s, const uint16_t value, const size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		s[i] = value;
	}
}

static void dwordset(uint32_t* restrict s, const uint32_t value, const size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		s[i] = value;
	}
}

static void qwordset(uint64_t* restrict s, const uint64_t value, const size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		s[i] = value;
	}
}

inline static uint16_t swapbytesw(uint16_t s)
{
	uint16_t output = 0;

	output |= (uint8_t)s << 8;
	output |= (uint8_t)(s >> 8);

	return output;
}

inline static uint32_t swapbytesdw(uint32_t s)
{
	uint32_t output = 0;

	output |= ((uint8_t)s) << 24;
	output |= (uint8_t)(s >> 8) << 16;
	output |= (uint8_t)(s >> 16) << 8;
	output |= (uint8_t)(s >> 24);

	return output;
}

inline static uint64_t swapbytesqw(uint64_t s)
{
	uint64_t output = 0;

	output |= (uint64_t)((uint8_t)s) << 56;
	output |= (uint64_t)(uint8_t)(s >> 8) << 48;
	output |= (uint64_t)(uint8_t)(s >> 16) << 40;
	output |= (uint64_t)(uint8_t)(s >> 24) << 32;
	output |= (uint64_t)(uint8_t)(s >> 32) << 24;
	output |= (uint64_t)(uint8_t)(s >> 40) << 16;
	output |= (uint64_t)(uint8_t)(s >> 48) << 8;
	output |= (uint64_t)(uint8_t)(s >> 56);

	return output;
}

inline static uint8_t popcount(uint64_t s)
{
	uint8_t c;

	while (s != 0)
	{
		c += s & 1;
		s >>= 1;
	}

	return c;
}

#ifdef __cplusplus
}
#endif

#endif
