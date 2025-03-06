#ifndef LIB_LIBCSTRING_H
#define LIB_LIBCSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct CString
{
	char* data;
	size_t size;
	size_t capacity;
} CString;

CString* cstrinit(const char* str);
CString* cstrset(CString* cstr, const char* str);
void cstrclear(CString* cstr);
int cstrshrink(CString* cstr);
void cstrfree(CString* cstr);

#ifdef __cplusplus
}
#endif

#endif
