#pragma once

#include "defs.h"

void handleLoad(int argc, char** argv);
void printLoadErrMessage();
void clearWorkSpace();
void loadCommit(u32 index);
void reloadStage(u32 index);