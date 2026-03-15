#pragma once

#include "dirCopy.h"

#define REP_NAME "MyVCS_Rep"
#define CONFIG_FILE_NAME "MyVSC\\config.dat"
#define VERSIONS_FILE "MyVCS\\Versions"

#define SET "set"
#define COMMIT "commit"

typedef struct Config {
    char path[SIZE];
    u32 versionCount;
} Config;

i8 createRep();
i8 getRepPath(char* buff);
i8 addToReject(char* name);
i8 setRepository(char* path);