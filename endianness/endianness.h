#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

// checks system endianness
// true = little, false = big
bool chkend();
void tobigend64(uint8_t* buffer, uint64_t n);
void tobigend32f(uint8_t* buffer, float f);
void tobigend32(uint8_t* buffer, uint32_t n);
void tolitend32(uint8_t* buffer, uint32_t n);
uint32_t fromlitend32(uint8_t* buffer);
uint32_t frombigend32(uint8_t* buffer);

#ifdef __cplusplus
}
#endif

#endif
