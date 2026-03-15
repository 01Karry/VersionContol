#pragma once

#include "dirCopy.h"

#define REP_NAME "MyVCS_Rep"
#define CONFIG_FILE_NAME REP_NAME"\\config.dat"
#define VERSIONS_FILE REP_NAME"\\Versions"

#define SET "set"
#define COMMIT "commit"

typedef struct Config {
    char path[SIZE];
    u32 versionCount;
} Config;

i8 createRep();