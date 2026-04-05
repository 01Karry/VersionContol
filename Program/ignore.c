#include "ignore.h"

i8 getType(char* path) {
    struct stat Stats;
    stat(path, &Stats);

    if (S_ISDIR(Stats.st_mode)) return 1;
    else if(S_ISREG(Stats.st_mode)) return 0;
    return -1;
}

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

/* Возвращает 2 что бы отдчать от baseingore*/
i8 checkInMcpIgnore(char* name) {
    FILE* pIgnore = fopen(IGNORE_FILE_NAME, "r");
    if (pIgnore == NULL) return -1;

    char nameFromFile[PATH_SIZE];

    while (fgets(nameFromFile, PATH_SIZE, pIgnore) != NULL) {
        size_t len = strlen(nameFromFile);

        if (nameFromFile[len - 1] == '\n') nameFromFile[len - 1] = '\0';

        if (nameFromFile[0] == '.' && checkExtIgnore(name, nameFromFile)) {
            fclose(pIgnore);
            return 2;
        }
        if (strncmp(name, nameFromFile, PATH_SIZE) == 0) {
            fclose(pIgnore);
            return 2;
        }
    }

    fclose(pIgnore);
    return 0;
}

i8 isIgnore(char* source, char* name) {
    if (name == NULL) return -1;

    char fullPath[PATH_SIZE];
    sprintf(fullPath, "%s\\%s", source, name);
    
    if (checkBaseIgnore(name) || checkBaseIgnore(fullPath)) return 1;

    i8 isInFile = checkInMcpIgnore(name);
    if (isInFile) return isInFile;

    isInFile = checkInMcpIgnore(fullPath);
    if (isInFile) return isInFile;

    return 0;
}

void ignoreOutput(char* name, i8 flag) {
    if (flag == 2) printf("%s is ignored\n", name); 
}