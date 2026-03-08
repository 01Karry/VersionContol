#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dirCopy.h"
#include "userCommands.h"

void handleSetRep(char* path) {
    char buff[SIZE];
    if (getRepPath(buff) == 0)
        printf("Repository alredy exist!\n");
    else 
        setRepository(path);
}
