#ifndef RAND_H
#define RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

uint64_t rand64();
uint32_t rand32();
uint16_t rand16();
float randf();
float randf_range(const float min, const float max);
double randd();
double randd_range(const double min, const double max);
int64_t rand64_range(const int64_t min, const int64_t max);
uint64_t get_rseed();
void initrstate(const uint64_t seed);

#ifdef __cplusplus
}
#endif
#endif
