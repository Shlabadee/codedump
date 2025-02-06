#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xfilepath.h"

void XFP_free(XFilePath* xfp)
{
	if (xfp == NULL)
		return;
	if (xfp->directory)
		free(xfp->directory);
	if (xfp->filename)
		free(xfp->filename);
	if (xfp->ext)
		free(xfp->ext);

	xfp->directory = NULL;
	xfp->filename = NULL;
	xfp->ext = NULL;
}

XFilePath XFP_split(const char* path)
{
	XFilePath result = {NULL, NULL, NULL};

	if (path == NULL)
		return result;

	// Find the last directory separator (assume POSIX-style '/')
	const char* last_slash = strrchr(path, '/');

	// Get path
	if (last_slash != NULL)
	{
		size_t dir_length = (size_t)(last_slash - path);
		result.directory = (char*)malloc(dir_length + 1);
		strncpy(result.directory, path, dir_length);
		result.directory[dir_length] = '\0';
	}
	else
	{
		// No slash found => no directory component
		result.directory = (char*)malloc(1);
		result.directory[0] = '\0';
	}

	// Point to the start of the filename
	const char* filename_start = (last_slash != NULL) ? last_slash + 1 : path;

	// Find the last '.' in the filename part for the extension
	const char* last_dot = strrchr(filename_start, '.');
	if (last_dot != NULL)
	{
		// Get file extension
		size_t ext_len = strlen(last_dot + 1);
		result.ext = (char*)malloc(ext_len + 1);
		strcpy(result.ext, last_dot + 1);

		// Get filename without extension
		size_t fname_len = (size_t)(last_dot - filename_start);
		result.filename = (char*)malloc(fname_len + 1);
		strncpy(result.filename, filename_start, fname_len);
		result.filename[fname_len] = '\0';
	}
	else
	{
		// No '.' found => no extension
		result.ext = (char*)malloc(1);
		result.ext[0] = '\0';

		// The entire remaining part is the filename
		size_t fname_len = strlen(filename_start);
		result.filename = (char*)malloc(fname_len + 1);
		strcpy(result.filename, filename_start);
	}

	return result;
}

int XFP_normalize_windows_path(const char* path, char* out_path)
{
	if (!path || !out_path)
		return -1;

	const char* src = path;
	char* dst = out_path;
	while (*src)
	{
		if (*src == '\\')
		{
			// Write a slash only if the last character written wasn't already '/'
			if (dst == out_path || *(dst - 1) != '/')
				*dst++ = '/';

			// Skip all consecutive backslashes
			while (*src == '\\')
				src++;
		}
		else
		{
			*dst++ = *src++;
		}
	}
	*dst = '\0';

	return 0;
}
