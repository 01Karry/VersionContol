#include "rmUtils.h"

#include "ignoreUtils.h"

void rmFile(char* path) {
    remove(path);
}

i8 rmNEDir(char* path) {
    DIR* pDir = opendir(path);
    if (pDir == NULL) return -1;

    for (struct dirent* entry = readdir(pDir); entry != NULL; entry = readdir(pDir)) {
        if (isIgnore(path, entry->d_name) == 0) {
            char fullPath[PATH_MAX];
            sprintf(fullPath, "%s\\%s", path, entry->d_name);

            rmAny(fullPath);
        }
    }

    closedir(pDir);

    rmdir(path);

    return 0;
}

i8 rmAny(char* path) {
    if (isIgnore("", path) != 0) {
        printf("ignore\n");
        return 0;
    }

    i8 type = getType(path);

    switch (type) {
    case 0:
        rmFile(path);
        break;
    case 1:
        return rmNEDir(path);
        break;
    }

    return 0;
}