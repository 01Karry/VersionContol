#pragma once

#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#define SIZE 1024
#define BUFF_SIZE 512

#define REJECT_FILE_NAME "VCreject.txt"

typedef int8_t i8;
typedef uint32_t u32;
typedef uint8_t u8;

i8 isReject(char* name);
i8 getType(char* path);
void copyFile(char* source, char* dest);
void copyDir(char* source, char* destPath);