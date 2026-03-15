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

i8 createRep() {
    mkdir(REP_NAME);

    FILE* pCfg = fopen(CONFIG_FILE_NAME, "wb");
    if (pCfg == NULL) return 1;

    fclose(pCfg);

    mkdir(VERSIONS_FILE);
    
    return 0;
}