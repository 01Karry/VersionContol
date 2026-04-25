#pragma once

#include "defs.h"

void handleLog(int argc, char** argv);
void logAllCommits();
i8 logCommit(u32 commitIndex);
void printCurrPathCommits();
//void printLogErrMessage();
u8 isValidIndex(u32 commitIndex);