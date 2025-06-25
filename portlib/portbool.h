#ifndef PORTBOOL_LIBPORTBOOL_H
#define PORTBOOL_LIBPORTBOOL_H

/* not strictly necessary but just being consistent */
#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_PORTBOOL)                                                                      \
    || (!defined(USE_STDBOOL) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L))
typedef unsigned char bool;
	#define false 0
	#define true 1
#else
	#include <stdbool.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
