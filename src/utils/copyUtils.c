#include "utils\copyUtils.h"
#include "utils\ignoreUtils.h"

void copyFile(char* source, char* dest) {
    FILE* pSource = fopen(source, "rb");
    FILE* pDest = fopen(dest, "wb");

    int size;
    char buff[BUFF_SIZE];

    while ((size = fread(buff, 1, BUFF_SIZE, pSource)) > 0) {
        fwrite(buff, 1, size, pDest);
    }

    fclose(pSource);
    fclose(pDest);
}

void copyDir(char* source, char* destPath) {
    DIR* pSource = opendir(source);
    if (pSource == NULL) {
        printf("Can't open %s\n", source);
        return;
    }

    mkdir(destPath);

    DIR* pCopy = opendir(destPath);
    if (pCopy == NULL) {
        printf("Can't open destination directory!\n");
        return;
    }

    for (struct dirent* entry = readdir(pSource); entry != NULL; entry = readdir(pSource)) {
        i8 ignoreCode = isIgnore(source, entry->d_name);
        
        if (ignoreCode != 0) {
            ignoreOutput(entry->d_name, ignoreCode);
            continue;
        }

        char pathToSource[PATH_SIZE];
        sprintf(pathToSource, "%s\\%s", source, entry->d_name);

        char pathToDest[PATH_SIZE];
        sprintf(pathToDest, "%s\\%s", destPath, entry->d_name);
        
        copyAny(pathToSource, pathToDest);
    }

    closedir(pCopy);
    closedir(pSource);
}

i8 copyAny(char* source, char* destPath) {
    i8 ignoreCode = isIgnore("", source);

    ignoreOutput(source, ignoreCode);

    if (ignoreCode) return ignoreCode;

    i8 type = getType(source);

    switch (type) {
    case 0:
        copyFile(source, destPath);
        break;
    case 1:
        copyDir(source, destPath);
        break;
    }

    return 0;
}