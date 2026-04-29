#pragma once

#include "defs.h"

void handleUntrack(int argc, char** argv);
i8 isTracked(char* name);
void printNotTrackedErr(char* name);
i8 untrack(char* name);
