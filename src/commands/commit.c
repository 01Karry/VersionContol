#include "commands\commit.h"
#include "utils\repUtils.h"
#include "utils\copyUtils.h"
#include "utils\rmUtils.h"

#include "inclds.h"
#include <time.h>

void handleCommit(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
    }

    makeCommitDir();
    writeCData(argv[2]);

    copyStageToCommit();
    rmStage();

    updateConfig();
}

void getPathToCommitDir(char* path) {
    Config cfg;
    getConfig(&cfg);

    sprintf(path, "%s\\%s%d", VERSIONS_FILE, "c", cfg.commitCount);
}

void makeCommitDir() {
    char path[PATH_SIZE];
    getPathToCommitDir(path);

    mkdir(path);
}

// Родительский коммит, сообщение, автор, дата, время
i8 writeCData(char message[MESSAGE_SIZE]) {
    Config cfg;
    getConfig(&cfg);

    char cDataPath[PATH_SIZE];
    sprintf(cDataPath, "%s\\%s%d\\%s", VERSIONS_FILE, "c", cfg.commitCount, CDATA_FILE_NAME);

    time_t currTime = time(NULL);
    struct tm* time = localtime(&currTime);

    char strDate[STR_DATE_SIZE] = { 0 };
    char strTime[STR_TIME_SIZE] = { 0 };

    // %D - %m/%d/%y
    strftime(strDate, sizeof(strDate), "%D", time);
    
    // %T - %H:%M:%S
    strftime(strTime, sizeof(strTime), "%T", time);

    char formatedMessage[MESSAGE_SIZE] = { 0 };

    strcpy(formatedMessage, message);

    FILE* pCdata = fopen(cDataPath, "w");
    if (pCdata == NULL) return 1;

    fwrite(&cfg.currCommit, sizeof(cfg.currCommit), 1, pCdata);
    fwrite(formatedMessage, MESSAGE_SIZE, 1, pCdata);
    fwrite(cfg.userName, sizeof(cfg.userName), 1, pCdata);
    fwrite(strDate, sizeof(strDate), 1, pCdata);
    fwrite(strTime, sizeof(strTime), 1, pCdata);
    
    fclose(pCdata);

    return 0;
}

i8 updateConfig() {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r+");
    if (pCfg == NULL) return 1;

    Config cfg;
    getConfig(&cfg);

    fseek(pCfg, OFFSET_FOR_CURRENT, SEEK_SET);
    fwrite(&cfg.commitCount, sizeof(cfg.commitCount), 1, pCfg);

    ++cfg.commitCount;

    fseek(pCfg, OFFSET_FOR_COUNT, SEEK_SET);
    fwrite(&cfg.commitCount, sizeof(cfg.commitCount), 1, pCfg);

    fclose(pCfg);

    return 0;
}

void copyStageToCommit() {
    char path[PATH_SIZE];
    getPathToCommitDir(path);

    copyAny(STAGE_FILE_NAME, path);
}

void rmStage() {
    rmAny(STAGE_FILE_NAME);

    mkdir(STAGE_FILE_NAME);
}