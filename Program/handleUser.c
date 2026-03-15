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

void handleInit() {
    if (createRep() == 0) printf("RepCreated\n");
    else printf("Can't create Repository");
}
