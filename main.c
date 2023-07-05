#include <stdio.h>

#include "path.h"

int main(void) {
	const char *path = "../../foo/../bar//buzz";
	const char **seg = path_split(path);
	for (const char **p = seg; *p; p++) {
		printf("%s\n", *p);
	}
	return 0;
}
