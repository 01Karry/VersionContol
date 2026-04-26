#pragma once

#include "inclds.h"
#include "defs.h"

i8 isRepCreated();
void printNoRepError();
i8 getConfig(Config* cfg);
i8 getCdata(Cdata_t* dest, u32 commitIndex);
i8 isStageEmpty();
void printEmptyStageError();