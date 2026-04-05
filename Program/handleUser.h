#pragma once

#include "header.h"

#include "dirCopy.h"
#include "userCommands.h"
#include "repCheck.h"

void handleInit();
void handleAdd(int argc, char** argv);
void handleCommit(char* message);