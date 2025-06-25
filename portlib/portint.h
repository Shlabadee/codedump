#ifndef PORTINT_LIBPORTINT_H
#define PORTINT_LIBPORTINT_H

/* not strictly necessary but just being consistent */
#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_PORTINT)                                                                       \
    || (!defined(USE_STDINT) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L))
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;
#else
	#include <stdint.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
