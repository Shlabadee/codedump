#include <stddef.h>
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

	// Get directory
	if (last_slash != NULL)
	{
		size_t dir_length = (size_t)(last_slash - path);
		result.directory = malloc(dir_length + 1);
		if (result.directory)
		{
			strncpy(result.directory, path, dir_length);
			result.directory[dir_length] = '\0';
		}
	}
	else
	{
		// No directory part so return an empty string
		result.directory = malloc(1);
		if (result.directory)
			result.directory[0] = '\0';
	}

	// Point to the start of the filename
	const char* filename_start = (last_slash != NULL) ? last_slash + 1 : path;

	/*
	Determine the position of the dot that separates the filename from the extension. For a
	filename that starts with a dot (a hidden file), search for a dot after the first
	character.
	*/
	const char* last_dot = (filename_start[0] == '.') ? strrchr(filename_start + 1, '.')
	                                                  : strrchr(filename_start, '.');

	if (last_dot != NULL)
	{
		// Get file extension
		size_t ext_len = strlen(last_dot + 1);
		result.ext = malloc(ext_len + 1);
		if (result.ext)
			strcpy(result.ext, last_dot + 1);

		// Get filename
		size_t fname_len = (size_t)(last_dot - filename_start);
		result.filename = malloc(fname_len + 1);
		if (result.filename)
		{
			strncpy(result.filename, filename_start, fname_len);
			result.filename[fname_len] = '\0';
		}
	}
	else
	{
		/*
		No dot (or only a prefixed dot) found. Everything is part of the filename, and there's
		no extension.
		*/
		result.ext = malloc(1);
		if (result.ext)
			result.ext[0] = '\0';

		size_t fname_len = strlen(filename_start);
		result.filename = malloc(fname_len + 1);
		if (result.filename)
			strcpy(result.filename, filename_start);
	}

	return result;
}

size_t XFP_size(XFilePath* xfp, unsigned short flags)
{
	size_t len = 0;
	if (xfp == NULL)
		return len;

	if (flags & XFPDIRECTORY && xfp->directory[0] != '\0')
		len += strlen(xfp->directory) + 1; // for the suffixed `/`

	if (flags & XFPFILENAME && xfp->filename[0] != '\0')
		len += strlen(xfp->filename);

	if (flags & XFPEXT && xfp->ext[0] != '\0')
	{
		len += strlen(xfp->ext);
		// Adding dot
		if (flags & (XFPDIRECTORY | XFPFILENAME))
			++len;
	}

	// Return with NULL byte consideration
	return ++len;
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
