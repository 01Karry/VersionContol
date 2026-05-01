#include "commands\untrack.h"
#include "utils\ignoreUtils.h"
#include "utils\rmUtils.h"
#include "utils\repUtils.h"

#include "inclds.h"

void handleUntrack(int argc, char** argv) {
    if (isRepCreated() == 0) {
        printNoRepError();
        return;
    }

    for (int i = 2; i < argc; i++) {
        if (isTracked(argv[i])) {
            untrack(argv[i]);
            setStageStatus(STAGE_STATUS_CHANGED);
        }
        else
            printNotTrackedErr(argv[i]);
    }
}

i8 isTracked(char* name) {
    char fullPath[PATH_SIZE];
    sprintf(fullPath, "%s\\%s", STAGE_DIR_NAME, name);

    if (isValidName(fullPath)) return 1;

    return 0;
}

void printNotTrackedErr(char* name) {
    printf("%s wasn't tracked!\n", name);
}

void untrack(char* name) {
    char fullPath[PATH_SIZE];
    sprintf(fullPath, "%s\\%s", STAGE_DIR_NAME, name);

    if (checkBaseIgnore(name) == 1) {
        printf("You can't untrack %s", name);
        return;
    }

    baseIgnoreRmAny(fullPath);
}