#ifndef RAND_H
#define RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#define RANDFC_DEFAULT_SCALE 0.166666671633720397949f
#define RANDFCR_DEFAULT_SCALE 6.0f

#include <stdbool.h>
#include <stdint.h>

#include <string.h>

uint64_t rand64();
uint32_t rand32();
uint16_t rand16();
uint8_t rand8();

static inline float randf()
{
	const uint32_t MASK_SIGNIFICAND_F = ((1UL << 23) - 1UL);
	const uint32_t MASK_EXPONENT_F = (127UL << 23);
	float f;
	uint32_t i = (rand32() & MASK_SIGNIFICAND_F) | MASK_EXPONENT_F;
	memcpy(&f, &i, sizeof(f)); // f = *((float*)&i);
	return --f;
}

static inline double randd()
{
	const uint64_t MASK_SIGNIFICAND_D = ((1ULL << 52) - 1ULL);
	const uint64_t MASK_EXPONENT_D = (1023ULL << 52);
	double d;
	uint64_t i = (rand64() & MASK_SIGNIFICAND_D) | MASK_EXPONENT_D;
	memcpy(&d, &i, sizeof(d));
	return --d;
}

static inline float randf_range(float min, float max)
{
	return (randf() * (max - min)) + min;
}

static inline double randd_range(double min, double max)
{
	return (randd() * (max - min)) + min;
}

int64_t rand64_range(int64_t min, int64_t max);
int8_t rand8_range(int8_t min, int8_t max);
/*
bell curve random number, between [0, 1]
if `offset` == `0.5f`, set the scale to `RANDFC_DEFAULT_SCALE` to keep the RNG as centered as
possible (97.5%)
*/
float randfc(float offset, float scale);
/*
bell curve RNG between `min` and `max`
a smaller `scale` results in a wider curve and value range
a larger `scale` results in the opposite
use `RANDFCR_DEFAULT_SCALE` for default value
*/
float randfcr(float min, float max, float scale);
/*
biased boolean RNG
if `bias` == `0.5f`, no bias
if `bias` > `0.5f`, bias towards `true`
if `bias` < `0.5f`, bias towards `false`
*/
static inline bool randb(float bias)
{
	return randf() < bias;
}
uint64_t get_rseed();
void initrstate(uint64_t seed);
/*
ensure `yrstate` is an array with `4` elements
*/
void getrstate(uint64_t* yrstate);
/*
ensure `yrstate` is an array with `4` elements
*/
void setrstate(const uint64_t* yrstate);

#ifdef __cplusplus
}
#endif
#endif
