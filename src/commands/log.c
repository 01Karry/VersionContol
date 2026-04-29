#include "commands\log.h"

#include "inclds.h"
#include "utils\repUtils.h"

void handleLog(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
        return;
    }
    
    i32 option;

    optind = 2;

    if (argc == 2) {
        logAllCommits();
        return;
    }

    if ((option = getopt(argc, argv, "i:rl")) != -1) {
        switch (option) {
        case 'i': {
            u32 commitIndex = atoi(optarg);

            if (logCommit(commitIndex) != 0) {
                printLogErrMessage();
            }
            break;
        }
        case 'r': {
            Config cfg;
            getConfig(&cfg);

            printCurrPathCommits(cfg.currCommit);

            break;
        }
        case '?':
            printLogErrMessage();
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

void printLogErrMessage() {
    printf("Wrong usage!\n");
    printf("Use 'mcp log' to get all commits\n");
    printf("Use 'mcp log -i N' to print commit N\n");
    printf("Use 'mcp log -r' to print path from curr commit to c0\n");
}

void printCurrPathCommits(u32 start) {
    logCommit(start);

    Cdata_t cdata;
    getCdata(&cdata, start);

    if (cdata.parent == start) return;

    printCurrPathCommits(cdata.parent);
}