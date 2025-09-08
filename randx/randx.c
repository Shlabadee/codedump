#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <time.h>

#include "randx.h"

#define MASK_SIGNIFICAND_F ((1UL << 23) - 1UL)
#define MASK_EXPONENT_F (127UL << 23)
#define MASK_SIGNIFICAND_D ((1ULL << 52) - 1ULL)
#define MASK_EXPONENT_D (1023ULL << 52)
#define L_PI 3.14159274101257324219f

static inline uint64_t h_rol64(const uint64_t x, const uint64_t k)
{
	return (x << k) | (x >> (64 - k));
}

static inline uint64_t h_ror64(const uint64_t x, const uint64_t k)
{
	return (x >> k) | (x << (64 - k));
}

uint64_t randx64(RXstate* state)
{
	uint64_t result;
	uint64_t t;

	result = h_rol64(state->state[1] * 5, 7) * 9;
	t = state->state[1] << 17;

	state->state[2] ^= state->state[0];
	state->state[3] ^= state->state[1];
	state->state[1] ^= state->state[2];
	state->state[0] ^= state->state[3];

	state->state[2] ^= t;
	state->state[3] = h_rol64(state->state[3], 45);

	return result;
}

uint32_t randx32(RXstate* state)
{
	static uint64_t random_sample = 0;
	static uint8_t sample_counter = 0;
	uint32_t output;

	if (sample_counter == 0)
	{
		random_sample = randx64(state);
		sample_counter = 2;
	}

	output = (uint32_t)random_sample;
	random_sample >>= 32;
	--sample_counter;

	return output;
}

uint16_t randx16(RXstate* state)
{
	static uint64_t random_sample = 0;
	static uint8_t sample_counter = 0;
	uint16_t output;

	if (sample_counter == 0)
	{
		random_sample = randx64(state);
		sample_counter = 4;
	}

	output = (uint16_t)random_sample;
	random_sample >>= 16;
	--sample_counter;

	return output;
}

uint8_t randx8(RXstate* state)
{
	static uint64_t random_sample = 0;
	static uint8_t sample_counter = 0;
	uint8_t output;

	if (sample_counter == 0)
	{
		random_sample = randx64(state);
		sample_counter = 8;
	}

	output = (uint8_t)random_sample;
	random_sample >>= 8;
	--sample_counter;

	return output;
}

float randxf(RXstate* state)
{
	float f;
	const uint32_t i = (randx32(state) & MASK_SIGNIFICAND_F) | MASK_EXPONENT_F;
	memcpy(&f, &i, sizeof(f)); // f = *((float*)&i);
	return --f;
}

double randxd(RXstate* state)
{
	double d;
	const uint64_t i = (randx64(state) & MASK_SIGNIFICAND_D) | MASK_EXPONENT_D;
	memcpy(&d, &i, sizeof(d));
	return --d;
}

float randxf_range(RXstate* state, const float min, const float max)
{
	return (randxf(state) * (max - min)) + min;
}

double randxd_range(RXstate* state, const double min, const double max)
{
	return (randxd(state) * (max - min)) + min;
}

int64_t randx64_range(RXstate* state, int64_t min, int64_t max)
{
	int64_t signed_range = max - min + 1;
	uint64_t range = (uint64_t)signed_range;
	uint64_t threshold = UINT64_MAX - (UINT64_MAX % range);

	uint64_t rnd;
	do
	{
		rnd = randx64(state);
	}
	while (rnd >= threshold);

	return (int64_t)(rnd % range) + min;
}

int8_t randx8_range(RXstate* state, const int8_t min, const int8_t max)
{
	int range = (int)max - (int)min + 1;
	int threshold = INT8_MAX - (INT8_MAX % range);
	int r;

	do
	{
		r = randx8(state) & INT8_MAX;
	}
	while (r >= threshold);

	return (int8_t)((r % range) + min);
}

static inline float h_clamp(const float value, const float min, const float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	return value;
}

float randxfc(RXstate* state, const float offset, const float scale)
{
	const float u1 = randxf(state);
	const float u2 = randxf(state);
	const float z = sqrtf(-2.0f * logf(u1)) * cosf(2.0f * L_PI * u2);
	return h_clamp((z * scale) + offset, 0.0f, 1.0f);
}

float randxfcr(RXstate* state, const float min, const float max, const float scale)
{
	const float mean = 0.5f * (min + max);
	const float stdev = (max - min) / scale;
	const float u1 = randxf(state), u2 = randxf(state);
	const float r = sqrtf(-2.0f * logf(u1));
	const float theta = 2.0f * L_PI * u2;
	const float z = r * cosf(theta);
	return mean + (z * stdev);
}

#ifdef BASICSEED

uint64_t get_rxseed()
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
	#if defined __linux__ || defined __APPLE__ || defined __FreeBSD__
uint64_t get_rxseed()
{
	uint64_t seed;
	size_t rb;
	FILE* dev_urandom = NULL;

	dev_urandom = fopen("/dev/urandom", "rb");

	if (dev_urandom == NULL)
		return 1;

	rb = fread(&seed, 1, sizeof(seed), dev_urandom);

	if (rb != sizeof(seed))
		seed = 2;

	fclose(dev_urandom);
	return seed;
}

	#else
		#ifdef _WIN32

			#include <windows.h>

uint64_t get_rxseed()
{
	HCRYPTPROV hProvider = 0;
	uint64_t seed = 1;

	if (CryptAcquireContext(&hProvider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		if (CryptGenRandom(hProvider, sizeof(seed), (BYTE*)&seed))
		{
			CryptReleaseContext(hProvider, 0);
			return seed;
		}
		else
			printf("CryptGenRandom failed. Error: %lu\n", GetLastError());

		CryptReleaseContext(hProvider, 0);
	}
	else
	{
		printf("CryptAcquireContext failed. Error: %lu\n", GetLastError());
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

void initrxstate(RXstate* state, const uint64_t seed)
{
	state->state[0] = h_splitmix64(seed);
	state->state[1] = h_splitmix64(state->state[0]);
	state->state[2] = h_splitmix64(state->state[1]);
	state->state[3] = h_splitmix64(state->state[2]);
}
