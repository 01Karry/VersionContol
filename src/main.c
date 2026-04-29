#include "commands\init.h"
#include "commands\add.h"
#include "commands\commit.h"
#include "commands\log.h"
#include "commands\load.h"
#include "commands\untrack.h"
#include "utils\ignoreUtils.h"

#include <locale.h>

int main(int argc, char** argv) {
    setlocale(LC_ALL, "rus");
    
    if (argc < 2) {
        printf("No command!\n");
        return 1;
    }

    if (strcmp(argv[1], INIT) == 0) {
        handleInit(argc, argv);
    }

    else if (strcmp(argv[1], ADD) == 0) {
        handleAdd(argc, argv);
    }

    else if (strcmp(argv[1], COMMIT) == 0) {
        handleCommit(argc, argv);
    }

    else if (strcmp(argv[1], LOG) == 0) {
        handleLog(argc, argv);
    }

    else if (strcmp(argv[1], LOAD) == 0) {
        handleLoad(argc, argv);
    }

    else if (strcmp(argv[1], UNTRACK) == 0) {
        handleUntrack(argc, argv);
    }

    freeIgnoreArr();
    
    return 0;
}