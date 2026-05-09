#pragma once

#include "inclds.h"
#include "defs.h"

i8 isRepCreated();
void printNoRepError();
i8 getConfig(Config* cfg);
i8 getCdata(Cdata_t* dest, u32 commitIndex);
u8 isStageChanged();
void printEmptyStageError();
u8 isValidIndex(u32 commitIndex);
void setCurrCommit(u32 index);
i8 setStageStatus(u8 val);
i8 getStageStatus();
void clearStage();
i8 isFileSame(char* path1, char* path2);
i8 cmpDirToDir(char* dir1, char* dir2);
i8 isSameAny(char* path1, char* path2);