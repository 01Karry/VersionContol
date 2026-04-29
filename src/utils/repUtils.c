#include "utils\repUtils.h"

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