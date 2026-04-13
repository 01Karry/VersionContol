#include "commands\commit.h"
#include "utils\repUtils.h"

#include "inclds.h"
#include <time.h>

void handleCommit(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
    }

    makeCommitDir();
}

void getPathCommitDir(char* path) {
    Config cfg;
    getConfig(&cfg);

    sprintf(path, "%s\\%s%d", VERSIONS_FILE, "c", cfg.commitCount);
}

void makeCommitDir() {
    char path[PATH_SIZE];
    getPathCommitDir(path);

    mkdir(path);
}

i8 writeCData(char message[MESSAGE_SIZE]) {
    Config cfg;
    getConfig(&cfg);

    char cDataPath[PATH_SIZE];
    getPathCommitDir(&cDataPath);
    sprintf(cDataPath, "%s\\%s", cDataPath, CDATA_FILE_NAME);

    time_t currTime;
    time(&currTime);

    struct tm* time = localtime(&currTime);

    char strDate[STR_DATE_SIZE];
    // %D - %m/%d/%y
    strftime(strDate, sizeof(strDate), "%D", time);

    char strTime[STR_TIME_SIZE];
    // %T - %H:%M:%S
    strftime(strTime, sizeof(strTime), "%T", time);

    FILE* pCdata = fopen(cDataPath, "w");
    if (pCdata == NULL) return 1;

    fwrite(&cfg.currCommit, sizeof(cfg.currCommit), 1, pCdata);
    fwrite(message, MESSAGE_SIZE, 1, pCdata);
    fwrite(cfg.userName, sizeof(cfg.userName), 1, pCdata);
    fwrite(strDate, sizeof(strDate), 1, pCdata);
    fwrite(strTime, sizeof(strTime), 1, pCdata);
    
    fclose(pCdata);
    
    return 0;
}