#pragma once

#include "defs.h"

void handleLog(int argc, char** argv);
void logAllCommits();
i8 logCommit(commitIndex);
void printCurrPathCommits();
void printLogErrMessage();