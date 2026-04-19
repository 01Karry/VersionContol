#include "commands\add.h"
#include "utils\copyUtils.h"
#include "utils\repUtils.h"

i8 addToStage(char* fileName) {
    if (strcmp(".", fileName) == 0) {
        copyDir(".", STAGE_DIR_NAME);
        return 0;
    }

    char destPath[PATH_MAX];
    sprintf(destPath, "%s\\%s", STAGE_DIR_NAME, fileName);

	return copyAny(fileName, destPath);
}

void handleAdd(int argc, char** argv) {
    if (isRepCreated() == 0) {
        printNoRepError();
        return;
    }

    for (int i = 2; i < argc; i++) {
        addToStage(argv[i]);
    }
}
