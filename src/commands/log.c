#include "commands\log.h"

#include "inclds.h"
#include "utils\repUtils.h"

void handleLog(int argc, char** argv) {
    i32 option;
    u32 commitIndex;

    if (argc == 2) {
        logAllCommits();
        return;
    }

    while ((option = getopt(argc, argv + 1, "i:r")) != -1) {
        switch (option) {
        case 'i':
            commitIndex = atoi(optarg);

            if (logCommit(commitIndex) != 0) {
                //printLogErrMessage();
            }
            break;
        case 'r':
            //printCurrPathCommits();
            break;
        case '?':
            //printLogErrMessage();
            break;
        }
    }
}

void logAllCommits() {
    Config cfg;
    getConfig(&cfg);

    for (int i = 0; i < cfg.commitCount; i++) {
        logCommit(i);
    }
}

i8 logCommit(u32 commitIndex) {
    if (!isValidIndex(commitIndex)) return -1;

    Cdata_t data;
    getCdata(&data, commitIndex);

    printf("Commit: %d\n", commitIndex);
    printf("Author: %s\n", data.author);
    printf("Date: %s %s\n", data.date, data.time);
    printf("\t%s\n\n", data.message);

    return 0;
}

u8 isValidIndex(u32 commitIndex) {
    Config cfgData;
    getConfig(&cfgData);

    return commitIndex < cfgData.commitCount;
}