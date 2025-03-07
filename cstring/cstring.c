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

CString* cstrappend(CString* cstr, const char* str)
{
	size_t str_length = strlen(str);
	size_t new_size = cstr->size + str_length;

	if (new_size + 1 > cstr->capacity)
	{
		char* t_data = realloc(cstr->data, new_size + 1);

		if (t_data == NULL)
			return NULL;

		cstr->data = t_data;
		cstr->capacity = new_size + 1;
	}

	memcpy(cstr->data + cstr->size, str, str_length + 1);
	cstr->size = new_size;
	return cstr;
}

CString* cstrinsert(CString* cstr, const char* str, size_t pos)
{
	size_t insert_len, new_size;

	if (pos > cstr->size)
		return NULL;

	insert_len = strlen(str);
	new_size = cstr->size + insert_len;

	if (new_size + 1 > cstr->capacity)
	{
		char* t_data = realloc(cstr->data, new_size + 1);

		if (t_data == NULL)
			return NULL;

		cstr->data = t_data;
		cstr->capacity = new_size + 1;
	}

	memmove(cstr->data + pos + insert_len, cstr->data + pos, cstr->size - pos + 1);
	memcpy(cstr->data + pos, str, insert_len);
	cstr->size = new_size;
	return cstr;
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
