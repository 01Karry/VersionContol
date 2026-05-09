#include "commands\add.h"
#include "utils\copyUtils.h"
#include "utils\repUtils.h"
#include "utils\ignoreUtils.h"

i8 addToStage(char* fileName) {
    if (!isValidName(fileName)) {
        printf("%s doesn't exist!\n", fileName);
        return 2;
    }

    if (strcmp(".", fileName) == 0 && (cmpDirToDir(".", STAGE_DIR_NAME) == 0 || cmpDirToDir(STAGE_DIR_NAME, ".") == 0)) {
        copyDir(".", STAGE_DIR_NAME);
        return 0;
    }

    char destPath[PATH_SIZE];
    sprintf(destPath, "%s\\%s", STAGE_DIR_NAME, fileName);

    if (isSameAny(fileName, destPath) == 1) return 1;

	return copyAny(fileName, destPath);
}

void handleAdd(int argc, char** argv) {
    if (isRepCreated() == 0) {
        printNoRepError();
        return;
    }

    i8 changed = 0;

    for (int i = 2; i < argc; i++) {
        changed = addToStage(argv[i]) == 0 || changed == 1 ? 1 : 0;
    }

    if (changed == 1)
        setStageStatus(STAGE_STATUS_CHANGED);
}