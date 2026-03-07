#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "dirCopy.h"
#include "userCommands.h"

i8 setRepository(char* path) {
    char fullPath[SIZE];

    sprintf(fullPath, "%s\\%s", path, REP_NAME);

    FILE* pConfig;

    DIR* pRepository = opendir(fullPath);
}

i8 addToReject(char* name) {
    if (name == NULL) return -1;

    if (isReject(name) == 1) return 1;

    FILE* pReject = fopen(REJECT_FILE_NAME, "a");
    if (pReject == NULL) return -1;

    fprintf(pReject, "%s\n", name);

    fclose(pReject);

    return 0;
}