#ifndef SHLA_RAND_H
#define SHLA_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#define RANDFC_DEFAULT_SCALE 0.166666671633720397949f
#define RANDFCR_DEFAULT_SCALE 6.0f

#include <stdbool.h>
#include <stdint.h>

typedef struct RXstate
{
	uint64_t state[4];
} RXstate;

uint64_t randx64(RXstate* state);
uint32_t randx32(RXstate* state);
uint16_t randx16(RXstate* state);
uint8_t randx8(RXstate* state);
float randxf(RXstate* state);
float randxf_range(RXstate* state, const float min, const float max);
double randxd(RXstate* state);
double randxd_range(RXstate* state, const double min, const double max);
int64_t randx64_range(RXstate* state, const int64_t min, const int64_t max);
int8_t randx8_range(RXstate* state, const int8_t min, const int8_t max);
/*
bell curve random number, between [0, 1]
if `offset` == `0.5f`, set the scale to `RANDFC_DEFAULT_SCALE` to keep the RNG as centered as
possible (97.5%)
*/
float randxfc(RXstate* state, const float offset, const float scale);
/*
bell curve RNG between `min` and `max`
a smaller `scale` results in a wider curve and value range
a larger `scale` results in the opposite
use `RANDFCR_DEFAULT_SCALE` for default value
*/
float randxfcr(RXstate* state, const float min, const float max, const float scale);
/*
biased boolean RNG
if `bias` == `0.5f`, no bias
if `bias` > `0.5f`, bias towards `true`
if `bias` < `0.5f`, bias towards `false`
*/
static inline bool randxb(RXstate* state, const float bias)
{
	return randxf(state) < bias;
}
uint64_t get_rxseed();
void initrxstate(RXstate* state, const uint64_t seed);

#ifdef __cplusplus
}
#endif
#endif
