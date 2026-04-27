#pragma once

#include "inclds.h"
#include "defs.h"

void rmFile(char* path);
i8 rmNEDir(char* path);
i8 rmAny(char* path);
i8 baseIgnoreRmNEDir(char* path);
void baseIgnoreRmAny(char* path);