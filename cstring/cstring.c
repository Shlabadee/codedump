#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "cstring.h"

CString* cstrinit(const char* str)
{
	size_t str_length;
	CString* cstr = calloc(1, sizeof(*cstr));

	if (cstr == NULL)
		return NULL;

	str_length = strlen(str);
	cstr->data = calloc(str_length + 1, sizeof(*cstr->data));

	if (cstr->data == NULL)
	{
		free(cstr);
		return NULL;
	}

	strcpy(cstr->data, str);
	cstr->capacity = str_length + 1;
	cstr->size = str_length;

	return cstr;
}

CString* cstrset(CString* cstr, const char* str)
{
	size_t str_length;

	str_length = strlen(str);

	if (str_length + 1 > cstr->capacity)
	{
		char* t_data = realloc(cstr->data, str_length + 1);

		if (t_data == NULL)
			return NULL;

		cstr->data = t_data;
		cstr->capacity = str_length + 1;
	}

	strcpy(cstr->data, str);
	cstr->size = str_length;
	cstr->data[cstr->capacity - 1] = '\0';
	return cstr;
}

CString* cstrappend(CString* dest, const char* cstr)
{
	size_t suffix_len = strlen(suffix);
	size_t new_size = dest->size + suffix_len;

	if (new_size + 1 > dest->capacity)
	{
		char* t_data = realloc(dest->data, new_size + 1);

		if (t_data == NULL)
			return NULL;

		dest->data = t_data;
		dest->capacity = new_size + 1;
	}

	memcpy(dest->data + dest->size, suffix, suffix_len + 1);
	dest->size = new_size;
	return dest;
}

CString* cstrinsert(CString* cstr, const char* str, size_t pos)
{
	size_t insert_len, new_size;

	if (pos > dest->size)
		return NULL;

	insert_len = strlen(str);
	new_size = dest->size + insert_len;

	if (new_size + 1 > dest->capacity)
	{
		char* t_data = realloc(dest->data, new_size + 1);

		if (t_data == NULL)
			return NULL;

		dest->data = t_data;
		dest->capacity = new_size + 1;
	}

	memmove(dest->data + pos + insert_len, dest->data + pos, dest->size - pos + 1);
	memcpy(dest->data + pos, str, insert_len);
	dest->size = new_size;
	return dest;
}

void cstrclear(CString* cstr)
{
	memset(cstr->data, 0, cstr->capacity);
	cstr->size = 0;
}

int cstrshrink(CString* cstr)
{
	if (cstr->capacity == cstr->size + 1)
		return 1;

	char* t_data = realloc(cstr->data, cstr->size + 1);

	if (t_data == NULL)
		return 2;

	cstr->data = t_data;
	cstr->capacity = cstr->size + 1;

	return 0;
}

void cstrfree(CString* cstr)
{
	free(cstr->data);
	free(cstr);
}
