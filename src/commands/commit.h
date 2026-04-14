#pragma once

#include "defs.h"

void handleCommit(int argc, char** argv);
void getPathToCommitDir(char* path);
void makeCommitDir();
i8 writeCData(char message[MESSAGE_SIZE]);
i8 updateConfig();
void copyStageToCommit();
void clearStage();