#ifndef PORTLIMITS_LIBPORTLIMITS_H
#define PORTLIMITS_LIBPORTLIMITS_H

/* not strictly necessary but just being consistent */
#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_PORTLIMITS)                                                                    \
    || (!defined(USE_STDLIMITS) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L))
	#define CHAR_BIT 8
	#define SCHAR_MIN (-128)
	#define SCHAR_MAX 127
	#define UCHAR_MAX 255u
	#define CHAR_MIN SCHAR_MIN
	#define CHAR_MAX SCHAR_MAX
	#define SHRT_MIN (-32768)
	#define SHRT_MAX 32767
	#define USHRT_MAX 65535u
	#define INT_MIN (-2147483647l - 1l)
	#define INT_MAX 2147483647l
	#define UINT_MAX 4294967295ul
	#define LONG_MIN INT_MIN
	#define LONG_MAX INT_MAX
	#define ULONG_MAX UINT_MAX
	#define LLONG_MIN (-9223372036854775807ll - 1ll)
	#define LLONG_MAX 9223372036854775807ll
	#define ULLONG_MAX 18446744073709551615ull
#else
	#include <limits.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
