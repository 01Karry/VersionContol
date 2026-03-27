#pragma once

#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#define PATH_SIZE 512
#define BUFF_SIZE 512

#define IGNORE_FILE_NAME "mcpIgnore.txt"

typedef int8_t i8;
typedef uint32_t u32;
typedef uint8_t u8;

i8 isIgnore(char* name);
i8 getType(char* path);
void copyFile(char* source, char* dest);
void copyDir(char* source, char* destPath);