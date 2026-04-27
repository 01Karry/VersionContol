#include "commands\commit.h"
#include "utils\repUtils.h"
#include "utils\copyUtils.h"
#include "utils\rmUtils.h"
#include "utils\ignoreUtils.h"

#include "inclds.h"
#include <time.h>

void handleCommit(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
        return;
    }
    
    if (isStageEmpty()) {
        printEmptyStageError();
        return;
    }

    makeCommitDir();
    writeCData(argv[2]);

    copyStageToCommit();
    clearStage();

    updateConfig();
}

void getPathToCommitDir(char* path) {
    Config cfg;
    getConfig(&cfg);

    sprintf(path, "%s\\%s%d", VERSIONS_DIR, "c", cfg.commitCount);
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
    sprintf(cDataPath, "%s\\%s%d\\%s", VERSIONS_DIR, "c", cfg.commitCount, CDATA_FILE_NAME);

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
    fwrite(formatedMessage, sizeof(formatedMessage), 1, pCdata);
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

    noIgnoreCopyAny(STAGE_DIR_NAME, path);
}

void clearStage() {
    DIR* pDir = opendir(STAGE_DIR_NAME);
    if (pDir == NULL) return;

    for (struct dirent* entry = readdir(pDir); entry != NULL; entry = readdir(pDir)) {
        if (checkBaseIgnore(entry->d_name) == 0) {
            char fullPath[PATH_SIZE];
            sprintf(fullPath, "%s\\%s", STAGE_DIR_NAME, entry->d_name);

            baseIgnoreRmAny(fullPath);
        }
    }

    closedir(pDir);
}