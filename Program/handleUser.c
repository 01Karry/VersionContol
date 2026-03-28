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
    if (createRep() == 1) {
        printf("Can't create Repository\n");
        return;
    }

    if (makeCfg() == 1) {
        printf("Can't create config\n");
        return;
    }
    
    FILE* pReject = fopen(IGNORE_FILE_NAME, "w");
    if (pReject == NULL) {
        printf("Can't create %s\n", IGNORE_FILE_NAME);
        return;
    }

    if (setUserName() == 1) {
        printf("Can't set user name\n");
        return;
    }
}

void handleAdd(int argc, char** argv) {
    for (int i = 2; i < argc; i++) {
        addToStage(argv[i]);
    }
}
