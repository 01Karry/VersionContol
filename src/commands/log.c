#include "commands\log.h"

#include "inclds.h"

void handleLog(int argc, char** argv) {
    i32 option;

    if (argc == 2) {
        logAllCommits();
    }
    else if ((option = getopt(argc, argv, "c:r")) != -1) {
        switch (option) {
        case 'c':
            u32 commitIndex = atoi(optarg);

            if (logCommit(commitIndex) != 0) {
                printLogErrMessage();
            }
            break;
        case 'r':
            printCurrPathCommits();
            break;
        case '?':
            printLogErrMessage();
            break;
        }
    }
    else {
        printLogErrMessage();
    }
}