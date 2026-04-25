#pragma once

#include "inclds.h"
#include "defs.h"

void copyFile(char* source, char* dest);
void copyDir(char* source, char* dest);
i8 copyAny(char* source, char* destPath);
void noIgnoreCopyAny(char* source, char* destPath);
void noIgnoreCopyDir(char* source, char* destPath);