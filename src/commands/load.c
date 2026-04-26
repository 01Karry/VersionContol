#include "commands\load.h"

#include "inclds.h"
#include "repUtils.h"

void handleLoad(int argc, char** argv) {
    if (argc != 3 || !isValidIndex(argv[2])) {
        printLoadErrMessage();
    }

    clearWorkSpace();
    loadCommit(argv[2]);
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

    

    closedir(pWorkDir);
}