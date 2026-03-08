#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "dirCopy.h"

u8 checkExtReject(char* name, char* ext) {
    size_t extLen = strlen(ext);
    size_t nameLen = strlen(name);

    if (strncmp(name + nameLen - extLen, ext, extLen) == 0) return 1;

    return 0;
}

u8 checkBaseReject(char* name) {
    if (name == NULL) return -1;

    char baseReject[][SIZE] = { ".", ".." };

    for (int i = 0; i < sizeof(baseReject) / sizeof(baseReject[0]); i++) {
        if (strncmp(name, baseReject[i], SIZE) == 0) return 1;
    }

    return 0;
}

i8 checkInRejFile(char* name) {
    FILE* pReject = fopen(REJECT_FILE_NAME, "r");
    if (pReject == NULL) return -1;

    char nameRej[SIZE];

    while (fgets(nameRej, SIZE, pReject) != NULL) {
        size_t len = strlen(nameRej);

        if (nameRej[len - 1] == '\n') nameRej[len - 1] = '\0';

        printf("R : %s\n", nameRej);
        if (nameRej[0] == '.' && checkExtReject(name, nameRej)) {
            fclose(pReject);
            return 1;
        }
        if (strncmp(name, nameRej, SIZE) == 0) {
            fclose(pReject);
            return 1;
        }
    }

    fclose(pReject);
    return 0;
}

i8 isReject(char* name) {
    if (name == NULL) return -1;

    if (checkBaseReject(name)) return 1;

    i8 isInFile = checkInRejFile(name);

    if (isInFile) return isInFile;

    return 0;
}

i8 getType(char* path) {
    struct stat Stats;
    stat(path, &Stats);

    if (S_ISDIR(Stats.st_mode)) return 1;
    else if(S_ISREG(Stats.st_mode)) return 0;
    return -1;
}

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
    printf("Source : %s\n", source);
    DIR* pSource = opendir(source);
    if (pSource == NULL) {
        printf("Can't open source directory!\n");
        exit(-1);
    }

    mkdir(destPath);
    DIR* pCopy = opendir(destPath);
    if (pSource == NULL) {
        printf("Can't open destination directory!\n");
        exit(-1);
    }


    for (struct dirent* entry = readdir(pSource); entry != NULL; entry = readdir(pSource)) {
        if (!isReject(entry->d_name)) {
            char pathToSourceFile[SIZE];
            sprintf(pathToSourceFile, "%s\\%s", source, entry->d_name);

            char pathToDestFile[SIZE];
            sprintf(pathToDestFile, "%s\\%s", destPath, entry->d_name);
            
            i8 type = getType(pathToSourceFile);
            
            printf("Type : %d\n", type);
            switch (type) {
            case 0:
                copyFile(pathToSourceFile, pathToDestFile);
                break;
            case 1:
                copyDir(pathToSourceFile, pathToDestFile);
                break;
            }
        }
    }
    
    closedir(pCopy);
    closedir(pSource);
}