#ifndef XFILEPATH_H
#define XFILEPATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define XFPDIRECTORY 0b1
#define XFPFILENAME 0b10
#define XFPEXT 0b100
#define XFPEVERYTHING (XFPDIRECTORY | XFPFILENAME | XFPEXT)

typedef struct XFilePath
{
	char* directory;
	char* filename;
	char* ext;
} XFilePath;

XFilePath XFP_split(const char* path);
/*
Ensure `path` is an empty string that can contain all the strings in `xfp` plus a `/` and `.` if
needed. You can use `XFP_size` to get the full necessary size.
*/
void XFP_join(const XFilePath* xfp, char* path);
void XFP_free(XFilePath* xfp);
/*
Returns the total string size (which includes the `NULL`-terminator) of each path part.

`XFPDIRECTORY` = directory
`XFPFILENAME` = filename
`XFPEXT` = extension
*/
size_t XFP_size(XFilePath* xfp, unsigned short flags);
/*
Ensure `out_path` is at least the same size as `path` as this function does not allocate memory.
*/
int XFP_normalize_windows_path(const char* path, char* out_path);

#ifdef __cplusplus
}
#endif

#endif
