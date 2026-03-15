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

i8 getRepPath(char* buff) {
    FILE* pConfig = fopen(CONFIG_FILE_NAME, "r");
    if (pConfig == NULL) return -1;

    fread(buff, SIZE, 1, pConfig);

    fclose(pConfig);

    return 0;
}

i8 setRepository(char* path) {
    Config cfg = { { 0 }, 0 };

    sprintf(cfg.path, "%s\\%s", path, REP_NAME);

    FILE* pConfig = fopen(CONFIG_FILE_NAME, "wb");
    if (pConfig == NULL) return 1;

    fwrite(cfg.path, SIZE, 1, pConfig);
    fwrite(&cfg.versionCount, sizeof(cfg.versionCount), 1, pConfig);

    fclose(pConfig);

    mkdir(cfg.path);

    return 0;
}

i8 addToReject(char* name) {
    if (name == NULL) return -1;

    if (isReject(name) == 1) return 1;

    FILE* pReject = fopen(REJECT_FILE_NAME, "a");
    if (pReject == NULL) return -1;

    fprintf(pReject, "%s\n", name);

    fclose(pReject);

    return 0;
}