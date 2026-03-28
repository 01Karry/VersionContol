#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "dirCopy.h"
#include "userCommands.h"

u8 checkExtIgnore(char* name, char* ext) {
    size_t extLen = strlen(ext);
    size_t nameLen = strlen(name);

    if (strncmp(name + nameLen - extLen, ext, extLen) == 0) return 1;

    return 0;
}

u8 checkBaseIgnore(char* name) {
    if (name == NULL) return -1;

    char baseReject[][PATH_SIZE] = { ".", "..", REP_NAME };

    for (int i = 0; i < sizeof(baseReject) / sizeof(baseReject[0]); i++) {
        if (strncmp(name, baseReject[i], PATH_SIZE) == 0) return 1;
    }

    return 0;
}

i8 checkInMcpIgnore(char* name) {
    FILE* pReject = fopen(IGNORE_FILE_NAME, "r");
    if (pReject == NULL) return -1;

    char nameFromFile[PATH_SIZE];

    while (fgets(nameFromFile, PATH_SIZE, pReject) != NULL) {
        size_t len = strlen(nameFromFile);

        if (nameFromFile[len - 1] == '\n') nameFromFile[len - 1] = '\0';

        if (nameFromFile[0] == '.' && checkExtIgnore(name, nameFromFile)) {
            fclose(pReject);
            break;
        }
        if (strncmp(name, nameFromFile, PATH_SIZE) == 0) {
            fclose(pReject);
            break;
        }
    }

    fclose(pReject);
    return 2;
}

i8 isIgnore(char* name) {
    if (name == NULL) return -1;

    if (checkBaseIgnore(name)) return 1;

    i8 isInFile = checkInMcpIgnore(name);

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

i8 copy(char* source, char* destPath) {
    DIR* pSource = opendir(source);
    if (pSource == NULL) {
        printf("Can't add %s\n", source);
        return 1;
    }

    mkdir(destPath);

    DIR* pCopy = opendir(destPath);
    if (pSource == NULL) {
        printf("Can't open destination directory!\n");
        return 1;
    }

    for (struct dirent* entry = readdir(pSource); entry != NULL; entry = readdir(pSource)) {
        i8 ignoreCode = isIgnore(entry->d_name);

        ignoreOutput(entry->d_name, ignoreCode);

        if (ignoreCode == 0) {
            char pathToSourceFile[PATH_SIZE];
            sprintf(pathToSourceFile, "%s\\%s", source, entry->d_name);

            char pathToDestFile[PATH_SIZE];
            sprintf(pathToDestFile, "%s\\%s", destPath, entry->d_name);
            
            i8 type = getType(pathToSourceFile);
            
            switch (type) {
            case 0:
                copyFile(pathToSourceFile, pathToDestFile);
                break;
            case 1:
                return copy(pathToSourceFile, pathToDestFile);
                break;
            }
        }
    }
    
    closedir(pCopy);
    closedir(pSource);

    return 0;
}

void ignoreOutput(char* name, i8 flag) {
    if (flag == 2) printf("%s is ignored\n", name); 
}