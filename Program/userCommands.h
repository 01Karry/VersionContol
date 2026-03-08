#pragma once


#include "dirCopy.h"

#define REP_NAME "VCrepository"
#define CONFIG_FILE_NAME "VCconfig.bin"

#define SET "set"
#define COMMIT "commit"

typedef struct Config {
    char path[SIZE];
    u32 versionCount;
} Config;

i8 getRepPath(char* buff);
i8 addToReject(char* name);
i8 setRepository(char* path);