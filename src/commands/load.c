#include "commands\load.h"

#include "inclds.h"
#include "utils\repUtils.h"
#include "utils\rmUtils.h"
#include "utils\ignoreUtils.h"
#include "utils\copyUtils.h"

void handleLoad(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
        return;
    }

    if (argc != 3) {
        printLoadErrMessage();
        return;
    }

    u32 index = atoi(argv[2]);

    if (!isValidIndex(index)) {
        printLoadErrMessage();
        return;
    }

    clearWorkSpace();
    loadCommit(index);

    reloadStage(index);
    setStageStatus(STAGE_STATUS_UNCHANGED);
}

void printLoadErrMessage() {
    printf("Wrong usage error!\n");
    printf("Use 'mcp load N', to load commit N\n");
}

void clearWorkSpace() {
    DIR* pWorkDir = opendir(".");
    if (pWorkDir == NULL) {
        printf("Failed to clear current directory!\n");
        return;
    }

    for (struct dirent* entry = readdir(pWorkDir); entry != NULL; entry = readdir(pWorkDir)) {
        if (checkBaseIgnore(entry->d_name) == 0) {
            char fullPath[PATH_SIZE];
            sprintf(fullPath, "%s\\%s", ".", entry->d_name);

            baseIgnoreRmAny(fullPath);
        }
    }

    closedir(pWorkDir);
}

void loadCommit(u32 index) {
    char pathToCommit[PATH_SIZE];
    sprintf(pathToCommit, "%s\\%s%d", VERSIONS_DIR, "c", index);

    noIgnoreCopyAny(pathToCommit, ".");

    setCurrCommit(index);
}

void reloadStage(u32 index) {
    char pathToCommit[PATH_SIZE];
    sprintf(pathToCommit, "%s\\%s%d", VERSIONS_DIR, "c", index);

    clearStage();

    noIgnoreCopyAny(pathToCommit, STAGE_DIR_NAME);
}