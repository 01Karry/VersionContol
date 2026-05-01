#include "rmUtils.h"

#include "ignoreUtils.h"

void rmFile(char* path) {
    remove(path);
}

i8 baseIgnoreRmNEDir(char* path) {
    DIR* pDir = opendir(path);
    if (pDir == NULL) return -1;

    for (struct dirent* entry = readdir(pDir); entry != NULL; entry = readdir(pDir)) {
        if (checkBaseIgnore(entry->d_name) == 0) {
            char fullPath[PATH_SIZE];
            sprintf(fullPath, "%s\\%s", path, entry->d_name);

            baseIgnoreRmAny(fullPath);
        }
    }

    closedir(pDir);

    rmdir(path);

    return 0;
}

void baseIgnoreRmAny(char* path) {
    if (checkBaseIgnore(path) != 0) {
        return;
    }

    i8 type = getType(path);

    switch (type) {
    case 0:
        rmFile(path);
        break;
    case 1:
        baseIgnoreRmNEDir(path);
        break;
    }
}