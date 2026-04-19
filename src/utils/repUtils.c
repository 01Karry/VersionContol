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

    fclose(pCfg);

    return 0;
}

i8 getCdata(Cdata_t* dest, u32 commitIndex) {
    char pathToCdata[PATH_MAX];
    sprintf(pathToCdata, "%s\\c%d", VERSIONS_DIR, commitIndex);

    FILE* pCData = fopen(pathToCdata, "r");
    if (pCData == NULL) return -1;

    fread(&dest->parent, sizeof(dest->parent), 1, pCData);
    fread(&dest->message, sizeof(dest->message), 1, pCData);
    fread(&dest->author, sizeof(dest->author), 1, pCData);
    fread(&dest->date, sizeof(dest->date), 1, pCData);
    fread(&dest->time, sizeof(dest->time), 1, pCData);

    fclose(pCData);

    return 0;
}