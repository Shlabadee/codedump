#ifndef XFILEPATH_H
#define XFILEPATH_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct XFilePath
{
	char* directory;
	char* filename;
	char* ext;
} XFilePath;

XFilePath XFP_split(const char* path);
void XFP_free(XFilePath* xfp);
/*
Ensure `out_path` is at least the same size as `path` as this function does not allocate memory.
*/
int XFP_normalize_windows_path(const char* path, char* out_path);

#ifdef __cplusplus
}
#endif

#endif
