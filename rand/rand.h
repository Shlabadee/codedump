#ifndef SHLA_RAND_H
#define SHLA_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#define RANDFC_DEFAULT_SCALE 0.166666671633720397949f
#define RANDFCR_DEFAULT_SCALE 6.0f

#include <stdbool.h>
#include <stdint.h>

uint64_t rand64();
uint32_t rand32();
uint16_t rand16();
uint8_t rand8();
float randf();
float randf_range(const float min, const float max);
double randd();
double randd_range(const double min, const double max);
int64_t rand64_range(const int64_t min, const int64_t max);
int8_t rand8_range(const int8_t min, const int8_t max);
/*
bell curve random number, between [0, 1]
if `offset` == `0.5f`, set the scale to `RANDFC_DEFAULT_SCALE` to keep the RNG as centered as
possible (97.5%)
*/
float randfc(const float offset, const float scale);
/*
bell curve RNG between `min` and `max`
a smaller `scale` results in a wider curve and value range
a larger `scale` results in the opposite
use `RANDFCR_DEFAULT_SCALE` for default value
*/
float randfcr(const float min, const float max, const float scale);
/*
biased boolean RNG
if `bias` == `0.5f`, no bias
if `bias` > `0.5f`, bias towards `true`
if `bias` < `0.5f`, bias towards `false`
*/
static inline bool randb(const float bias)
{
	return randf() < bias;
}
uint64_t get_rseed();
void initrstate(const uint64_t seed);
/*
ensure `yrstate` is an array with `4` elements
*/
void getrstate(uint64_t* yrstate);
/*
ensure `yrstate` is an array with `4` elements
*/
void setrstate(uint64_t* yrstate);

#ifdef __cplusplus
}
#endif
#endif
