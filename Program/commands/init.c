#include "init.h"

i8 createRep() {
    mkdir(REP_NAME);
    mkdir(VERSIONS_FILE);
    mkdir(STAGE_FILE_NAME);

    makeCfg();
    
    return 0;
}

i8 makeCfg() {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "wb");
    if (pCfg == NULL) return 1;

    Config cfgData = { .userName = { 0 }, .commitCount = 0, .currCommit = 0 };

    fwrite(&cfgData.commitCount, sizeof(cfgData.commitCount), 2, pCfg);
    fwrite(cfgData.userName, sizeof(cfgData.userName), 1, pCfg);

    fclose(pCfg);

    return 0;
}

i8 writeNameToCFG(char* name) {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r+");
    if (pCfg == NULL) return 1;

    fseek(pCfg, OFFSET_FOR_NAME, SEEK_SET);

    fwrite(name, USER_NAME_SIZE, 1, pCfg);

    return 0;
}

i8 setUserName() {
    printf("Enter your name : ");

    char buff[USER_NAME_SIZE] = { 0 };

    gets_s(buff, USER_NAME_SIZE);

    return writeNameToCFG(buff);
}

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