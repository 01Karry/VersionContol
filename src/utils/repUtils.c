#include "utils\repUtils.h"

#include "utils\ignoreUtils.h"
#include "utils\rmUtils.h"

i8 isRepCreated() {
    DIR* pRep = opendir(REP_NAME);
    if (pRep == NULL) return 0;
    closedir(pRep);

    DIR* pStage = opendir(STAGE_DIR_NAME);
    if (pStage == NULL) return 0;
    closedir(pStage);

    DIR* pVersions = opendir(VERSIONS_DIR);
    if (pVersions == NULL) return 0;
    closedir(pVersions);

    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r");
    if (pCfg == NULL) return 0;
    fclose(pCfg);

    return 1;
}

void printNoRepError() {
    printf("You have to initialize repsitory!\n");
}

i8 getConfig(Config* cfg) {
    if (cfg == NULL) return 1;
    
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r");
    if (pCfg == NULL) return 1;

    fseek(pCfg, OFFSET_FOR_CURRENT, SEEK_SET);
    fread(&cfg->currCommit, sizeof(cfg->currCommit), 1, pCfg);

    fseek(pCfg, OFFSET_FOR_COUNT, SEEK_SET);
    fread(&cfg->commitCount, sizeof(cfg->commitCount), 1, pCfg);

    fseek(pCfg, OFFSET_FOR_NAME, SEEK_SET);
    fread(&cfg->userName, sizeof(cfg->userName), 1, pCfg);

    fseek(pCfg, OFFSET_FOR_STAGE_STATUS, SEEK_SET);
    fread(&cfg->stageStatus, sizeof(cfg->stageStatus), 1, pCfg);

    fclose(pCfg);

    return 0;
}

i8 getCdata(Cdata_t* dest, u32 commitIndex) {
    char pathToCdata[PATH_SIZE];
    sprintf(pathToCdata, "%s\\c%d\\%s", VERSIONS_DIR, commitIndex, CDATA_FILE_NAME);


    FILE* pCData = fopen(pathToCdata, "r");
    if (pCData == NULL) return -1;
    
    fseek(pCData, OFFSET_FOR_PARENT, SEEK_SET);
    fread(&dest->parent, sizeof(dest->parent), 1, pCData);

    fseek(pCData, OFFSET_FOR_MESSAGE, SEEK_SET);
    fread(&dest->message, sizeof(dest->message), 1, pCData);

    fseek(pCData, OFFSET_FOR_AUTHOR, SEEK_SET);
    fread(&dest->author, sizeof(dest->author), 1, pCData);

    fseek(pCData, OFFSET_FOR_DATE, SEEK_SET);
    fread(&dest->date, sizeof(dest->date), 1, pCData);

    fseek(pCData, OFFSET_FOR_TIME, SEEK_SET);
    fread(&dest->time, sizeof(dest->time), 1, pCData);

    fclose(pCData);

    return 0;
}

i8 isStageEmpty() {
    DIR* pStage = opendir(STAGE_DIR_NAME);
    if (pStage == NULL) {
        printNoRepError();
        return -1;
    }

    for (struct dirent* entry = readdir(pStage); entry != NULL; entry = readdir(pStage)) {
        if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0) {
            closedir(pStage);
            return 0;
        }
    }

    closedir(pStage);
    return 1;
}

u8 isStageChanged() {
    return getStageStatus() == 1;
}

void printEmptyStageError() {
    printf("You need to add files to Stage!\n");
}

u8 isValidIndex(u32 commitIndex) {
    Config cfgData;
    getConfig(&cfgData);

    return commitIndex < cfgData.commitCount;
}

void setCurrCommit(u32 index) {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r+");
    if (pCfg == NULL) return;

    fseek(pCfg, OFFSET_FOR_CURRENT, SEEK_SET);
    fwrite(&index, sizeof (index), 1, pCfg);

    fclose(pCfg);
}

i8 setStageStatus(u8 val) {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r+");
    if (pCfg == NULL) return -1;

    fseek(pCfg, OFFSET_FOR_STAGE_STATUS, SEEK_SET);
    fwrite(&val, sizeof(val), 1, pCfg);

    fclose(pCfg);

    return 0;
}

i8 getStageStatus() {
    FILE* pCfg = fopen(CONFIG_FILE_NAME, "r");
    if (pCfg == NULL) return -1;

    u8 status;

    fseek(pCfg, OFFSET_FOR_STAGE_STATUS, SEEK_SET);
    fread(&status, sizeof(status), 1, pCfg);

    fclose(pCfg);

    return status;
}

void clearStage() {
    DIR* pDir = opendir(STAGE_DIR_NAME);
    if (pDir == NULL) return;

    for (struct dirent* entry = readdir(pDir); entry != NULL; entry = readdir(pDir)) {
        if (checkBaseIgnore(entry->d_name) == 0) {
            char fullPath[PATH_SIZE];
            sprintf(fullPath, "%s\\%s", STAGE_DIR_NAME, entry->d_name);

            baseIgnoreRmAny(fullPath);
        }
    }

    closedir(pDir);
}

// Сравнивает переданный файл с файлов в Stage
i8 isFileSame(char* path1, char* path2) {
    FILE* pFile1 = fopen(path1, "r");
    if (pFile1 == NULL) {
        return -1;
    }

    FILE* pFile2 = fopen(path2, "r");
    if (pFile2 == NULL) {
        fclose(pFile1);
        return 0;
    }

    u8 buff1[BUFF_SIZE], buff2[BUFF_SIZE];

    if (_filelengthi64(fileno(pFile1)) != _filelengthi64(fileno(pFile2))) {
        fclose(pFile1);
        fclose(pFile2);

        return 0;
    }

    u32 size = fread(buff1, 1, BUFF_SIZE, pFile1);

    while (size > 0) {
        // -1 считаные размеры должны совпадать
        if (fread(buff2, 1, BUFF_SIZE, pFile2) != size) {
            fclose(pFile1);
            fclose(pFile2);

            return -1;
        }
        if (memcmp(buff1, buff2, size) != 0) {
            fclose(pFile1);
            fclose(pFile2);

            return 0;
        }
    }

    fclose(pFile1);
    fclose(pFile2);

    return 1;
}

// возвращает 1 если одниковые
i8 cmpDirToDir(char* dir1, char* dir2) {
    DIR* pDir1 = opendir(dir1);
    if (pDir1 == NULL) return 0;

    DIR* pDir2 = opendir(dir2);
    if (pDir2 == NULL) {
        closedir(pDir1);

        return 0;
    }
    closedir(pDir2);

    for (struct dirent* entry = readdir(pDir1); entry != NULL; entry = readdir(pDir1)) {
        if (isIgnore(dir1, entry->d_name) != 0) continue;
        char insideDir1Path[PATH_SIZE];
        char insideDir2Path[PATH_SIZE];

        sprintf(insideDir1Path, "%s\\%s", dir1, entry->d_name);
        sprintf(insideDir2Path, "%s\\%s", dir2, entry->d_name);

        if (isSameAny(insideDir1Path, insideDir2Path) == 0) return 0;
    }

    return 1;
}

i8 isSameAny(char* path1, char* path2) {
    if (isIgnore(".", path1) != 0 || isIgnore(".", path2) != 0) return 1;

    i8 type = getType(path1);

    if (type != getType(path2)) return 0;

    if (type == 0) {
        return isFileSame(path1, path2);
    }

    if (type == -1) return -1;

    if (cmpDirToDir(path1, path2) == 1 && cmpDirToDir(path2, path1) == 1) return 1;

    return 0;
}