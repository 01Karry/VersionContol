#pragma once

#include "inclds.h"

#define PATH_SIZE 512
#define BUFF_SIZE 512

typedef int8_t i8;
typedef uint32_t u32;
typedef uint8_t u8;

#define IGNORE_FILE_NAME "mcpIgnore.txt"

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

#define CDATA_FILE_NAME "cdata.dat"
#define MESSAGE_SIZE 256

#define CDATA_PREW_OFFSET 0
#define CDATA_MESSAGE_OFFSET 4

typedef struct DataTime {
    u32 year;
    u8 data;
    u8 hour;
    u8 minutes;
    u8 seconds;
}
