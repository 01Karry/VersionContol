#pragma once

#include "defs.h"

void handleLog(int argc, char** argv);
void logAllCommits();
i8 logCommit(u32 commitIndex);
void printLogErrMessage();
void printCurrPathCommits(u32 start);