#pragma once
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// path_split("foo/bar") => {"foo", "bar", NULL}
const char **path_split(const char *path) {
	size_t capacity = 4, size = 0, end = 0;
	const char **top = (const char **)calloc(capacity, sizeof *top);

	while (*path) {
		while (*path && *path == '/') path++;
		if (!path) break;

		const char *p = path;
		while (*p && *p != '/') p++;

		size_t len = p - path;
		char *part = (char *)malloc(len + 1);
		memcpy(part, path, len);
		part[len] = '\0';
		if (*p) p++;
		path = p;

		if (strcmp(part, "..") == 0) {
			if (end) end--;
		} else if (strcmp(part, ".") != 0 && len > 0) {
			if (end == size && size == capacity) {
				capacity <<= 1;
				top = (const char **)realloc(top, capacity * sizeof *top);
			}
			top[end++] = part;
			if (size < end) size = end;
		} else {
			free(part);
		}
	}

	top[end] = NULL;
	return top;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
