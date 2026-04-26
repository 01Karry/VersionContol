#include "utils\ignoreUtils.h"

i8 getType(char* path) {
    struct stat Stats;
    stat(path, &Stats);

    if (S_ISDIR(Stats.st_mode)) return 1;
    else if (S_ISREG(Stats.st_mode)) return 0;
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

    char baseReject[][PATH_SIZE] = { ".", "..", REP_NAME, CDATA_FILE_NAME, CONFIG_FILE_NAME };

    for (int i = 0; i < sizeof(baseReject) / sizeof(baseReject[0]); i++) {
        if (strncmp(name, baseReject[i], PATH_SIZE) == 0) return 1;
    }

    return 0;
}

IgnoreSt ignoreVal = { NULL, 0 };

/* Возвращает 2 что бы отлчать от baseingore*/
i8 checkInMcpIgnore(char* name) {
    if (ignoreVal.arr == NULL) createIgnoreArray();
    if (ignoreVal.arr == NULL) return 0;

    for (u32 i = 0; i < ignoreVal.size; i++) {
        if (ignoreVal.arr[i][0] == '.' && checkExtIgnore(name, ignoreVal.arr[i])) {
            return 2;
        }

        if (strncmp(name, ignoreVal.arr[i], PATH_SIZE) == 0) {
            return 2;
        }
    }

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

void createIgnoreArray() {
    u32 malSize = 0;
    ignoreVal.size = 0;

    FILE* pIgnore = fopen(IGNORE_FILE_NAME, "r");
    if (pIgnore == NULL) return;

    char buff[PATH_SIZE];

    while (fgets(buff, PATH_SIZE, pIgnore) != NULL) ++malSize;
    rewind(pIgnore);

    ignoreVal.arr = malloc(sizeof(char*) * malSize);
    if (ignoreVal.arr == NULL) {
        fclose(pIgnore);
        return;
    }

    for (u32 i = 0; i < malSize; i++) {
        ignoreVal.arr[i] = malloc(sizeof(char) * PATH_SIZE);
        if (ignoreVal.arr[i] == NULL) {
            fclose(pIgnore);
            freeIgnoreArr();

            return;
        }

        ignoreVal.size++;

        fgets(ignoreVal.arr[i], PATH_SIZE, pIgnore);

        size_t len = strlen(ignoreVal.arr[i]);
        if (ignoreVal.arr[i][len - 1] == '\n') ignoreVal.arr[i][len - 1] = '\0';
    }

    fclose(pIgnore);
}

void freeIgnoreArr() {
    for (u32 i = 0; i < ignoreVal.size; i++) free(ignoreVal.arr[i]);
    free(ignoreVal.arr);

    ignoreVal.arr = NULL;
    ignoreVal.size = 0;
}