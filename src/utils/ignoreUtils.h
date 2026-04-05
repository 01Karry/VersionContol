#pragma once

#include "inclds.h"
#include "defs.h"

i8 getType(char* path);
u8 checkExtIgnore(char* name, char* ext);
u8 checkBaseIgnore(char* name);
i8 checkInMcpIgnore(char* name);
i8 isIgnore(char* source, char* name);
void ignoreOutput(char* name, i8 flag);