#include "add.h"

i8 addToStage(char* fileName) {
    if (strcmp(".", fileName) == 0) {
        copyDir(".", STAGE_FILE_NAME);
        return 0;
    }

    char destPath[PATH_SIZE];
    sprintf(destPath, "%s\\%s", STAGE_FILE_NAME, fileName);

	return copyAny(fileName, destPath);
}