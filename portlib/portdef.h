#ifndef PORTDEF_LIBPORTDEF_H
#define PORTDEF_LIBPORTDEF_H

/* not strictly necessary but just being consistent */
#ifdef __cplusplus
extern "C" {
#endif

typedef signed long long int ssize_t;

#if defined(USE_PORTDEF)                                                                       \
    || (!defined(USE_STDDEF) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L))
typedef unsigned long long int size_t;
#else
	#include <stddef.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
