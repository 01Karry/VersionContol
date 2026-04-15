#pragma once

#include "inclds.h"
#include "defs.h"

#define PATH_SIZE 512
#define BUFF_SIZE 512

#define IGNORE_FILE_NAME "mcpIgnore.txt"

typedef int8_t i8;
typedef uint32_t u32;
typedef uint8_t u8;

void copyFile(char* source, char* dest);
void copyDir(char* source, char* dest);
i8 copyAny(char* source, char* destPath);
void noIgnoreCopyAny(char* source, char* destPath);
void noIgnoreCopyDir(char* source, char* destPath);