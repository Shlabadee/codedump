#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include "rand.h"

// 0 00000000 11111111111111111111111
#define MASK_SIGNIFICAND_F UINT32_C(0b00000000011111111111111111111111)
// 0 01111111 00000000000000000000000
#define MASK_EXPONENT_F UINT32_C(0b00111111100000000000000000000000)
// 0 00000000000 1111111111111111111111111111111111111111111111111111
#define MASK_SIGNIFICAND_D                                                                     \
	UINT64_C(0b0000000000001111111111111111111111111111111111111111111111111111)
// 0 01111111111 0000000000000000000000000000000000000000000000000000
#define MASK_EXPONENT_D                                                                        \
	UINT64_C(0b0011111111110000000000000000000000000000000000000000000000000000)

static uint64_t xstate[4];

static inline uint64_t h_rol64(const uint64_t x, const uint64_t k)
{
	return (x << k) | (x >> (64 - k));
}

static inline uint64_t h_ror64(const uint64_t x, const uint64_t k)
{
	return (x >> k) | (x << (64 - k));
}

uint64_t rand64()
{
	uint64_t result;
	uint64_t t;

	result = h_rol64(xstate[1] * 5, 7) * 9;
	t = xstate[1] << 17;

	xstate[2] ^= xstate[0];
	xstate[3] ^= xstate[1];
	xstate[1] ^= xstate[2];
	xstate[0] ^= xstate[3];

	xstate[2] ^= t;
	xstate[3] = h_rol64(xstate[3], 45);

	return result;
}

uint32_t rand32()
{
	static uint64_t random_sample = 0;
	static uint8_t sample_counter = 0;
	uint32_t output;

	if (sample_counter == 0)
	{
		random_sample = rand64();
		sample_counter = 2;
	}

	output = (uint32_t)random_sample;
	random_sample >>= 32;
	--sample_counter;

	return output;
}

uint16_t rand16()
{
	static uint64_t random_sample = 0;
	static uint8_t sample_counter = 0;
	uint16_t output;

	if (sample_counter == 0)
	{
		random_sample = rand64();
		sample_counter = 4;
	}

	output = (uint16_t)random_sample;
	random_sample >>= 16;
	--sample_counter;

	return output;
}

float randf()
{
	float f;
	uint32_t i = (rand32() & MASK_SIGNIFICAND_F) | MASK_EXPONENT_F;
	memcpy(&f, &i, sizeof(f)); // f = *((float*)&i);
	return --f;
}

double randd()
{
	double d;
	uint64_t i = (rand64() & MASK_SIGNIFICAND_D) | MASK_EXPONENT_D;
	memcpy(&d, &i, sizeof(d));
	return --d;
}

float randf_range(const float min, const float max)
{
	return (randf() * (max - min)) + min;
}

double randd_range(const double min, const double max)
{
	return (randd() * (max - min)) + min;
}

int64_t rand64_range(const int64_t min, const int64_t max)
{
	const uint64_t range = max - min + 1;
	const uint64_t max_unbiased = INT64_MAX - (INT64_MAX % range);
	int64_t result;

	do
	{
		result = (int64_t)rand64() & INT64_MAX;
	}
	while (result >= max_unbiased);

	return (result % range) + min;
}

#ifdef BASICSEED

uint64_t get_rseed()
{
	const uint64_t base_seed = 0xfdedceb10fd672d1;
	uint64_t timestamp = time(0);
	timestamp ^= h_rol64(timestamp, 33);
	timestamp *= 0xff51afd7ed558ccdULL;
	timestamp ^= h_ror64(timestamp, 33);
	timestamp *= 0xc4ceb9fe1a85ec53ULL;
	timestamp ^= h_rol64(timestamp, 33);
	return timestamp ^ base_seed;
}
#else
	#if defined __linux__ || defined __APPLE__ || __FreeBSD__
uint64_t get_rseed()
{
	uint64_t seed;
	size_t rb;
	FILE* dev_urandom = NULL;

	dev_urandom = fopen("/dev/urandom", "rb");

	if (dev_urandom == NULL)
	{
		return 1;
	}

	rb = fread(&seed, 1, sizeof(seed), dev_urandom);

	if (rb != sizeof(seed))
	{
		seed = 2;
	}

	fclose(dev_urandom);
	return seed;
}

	#else
		#ifdef _WIN32

			#include <wincrypt.h>
			#include <windows.h>

uint64_t get_rseed()
{
	HCRYPTPROV hProvider = 0;
	uint64_t seed = 1;

	if (CryptAcquireContext(&hProvider, NULL, NULL, PROV_RSA_FULL, 0))
	{
		CryptGenRandom(hProvider, sizeof(seed), (BYTE*)&seed);
		CryptReleaseContext(hProvider, 0);
	}

	return seed;
}

		#endif
	#endif
#endif

static uint64_t h_splitmix64(const uint64_t x)
{
	uint64_t z = (x + 0x9e3779b97f4a7c15ULL);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
	z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
	return z ^ (z >> 31);
}

void initrstate(const uint64_t rseed)
{
	xstate[0] = h_splitmix64(rseed);
	xstate[1] = h_splitmix64(xstate[0]);
	xstate[2] = h_splitmix64(xstate[1]);
	xstate[3] = h_splitmix64(xstate[2]);
}
