#pragma once

#include "dirCopy.h"

#define REP_NAME "mcpRep"
#define CONFIG_FILE_NAME REP_NAME"\\config.dat"
#define VERSIONS_FILE REP_NAME"\\Versions"
#define STAGE_FILE_NAME REP_NAME"\\Stage"

#define INIT "init"
#define USER "user"
#define COMMIT "commit"
#define ADD "add"

#define USER_NAME_SIZE 128

#define OFFSET_FOR_NAME 8
#define OFFSET_FOR_COUNT 4 
#define OFFSET_FOR_CURRENT 0

typedef struct Config {
    char userName[USER_NAME_SIZE];
    u32 commitCount;
    u32 currCommit;
} Config;

i8 createRep();
i8 makeCfg();
i8 writeNameToCFG(char* name);
i8 setUserName();
i8 addToStage(char* name);
i8 addcDataFile(char* message);