#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "dirCopy.h"

i8 addToReject(char* name) {
    if (name == NULL) return -1;

    if (isReject(name) == 1) return 1;

    FILE* pReject = fopen(REJECT_FILE_NAME, "a");
    if (pReject == NULL) return -1;

    fprintf(pReject, "%s\n", name);

    fclose(pReject);

    return 0;
}