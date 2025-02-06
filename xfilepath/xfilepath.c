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

	if (last_slash != NULL)
	{
		size_t dir_length = (size_t)(last_slash - path + 1);
		result.directory = malloc(dir_length + 1);

		if (result.directory)
		{
			strncpy(result.directory, path, dir_length);
			result.directory[dir_length] = '\0';
		}
	}
	else
	{
		// If first character is '/', set directory to "/"
		if (path[0] == '/')
		{
			result.directory = malloc(2);

			if (result.directory)
				strcpy(result.directory, "/");
		}
		else
		{
			result.directory = malloc(1);

			if (result.directory)
				result.directory[0] = '\0';
		}
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

	// Validate that the extension is not just spaces
	if (last_dot != NULL && *(last_dot + 1) != '\0'
	    && strspn(last_dot + 1, " ") != strlen(last_dot + 1))
	{
		size_t ext_len = strlen(last_dot + 1);
		result.ext = malloc(ext_len + 1);

		if (result.ext)
			strcpy(result.ext, last_dot + 1);

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

void XFP_join(const XFilePath* xfp, char* path)
{
	if (xfp == NULL || path == NULL)
		return;

	// Ensure path starts empty
	path[0] = '\0';
	size_t curpos = 0;

	if (xfp->directory && xfp->directory[0] != '\0')
	{
		strcat(path, xfp->directory);
		curpos += strlen(xfp->directory);
	}

	if (xfp->filename && xfp->filename[0] != '\0')
	{
		strcat(path + curpos, xfp->filename);
		curpos += strlen(xfp->filename);
	}

	if (xfp->ext && xfp->ext[0] != '\0')
	{
		strcat(path + curpos, ".");
		strcat(path + curpos, xfp->ext);
	}
}

size_t XFP_size(XFilePath* xfp, unsigned short flags)
{
	size_t len = 0;
	if (xfp == NULL)
		return len;

	if (flags & XFPDIRECTORY && xfp->directory[0] != '\0')
		len += strlen(xfp->directory);

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
