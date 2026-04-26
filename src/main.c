#include "commands\init.h"
#include "commands\add.h"
#include "commands\commit.h"
#include "commands\log.h"
#include "commands\load.h"
#include "utils\ignoreUtils.h"

int main(int argc, char** argv) {
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

    else if (strcmp(argv[1], COMMIT) == 0 && argc == 3) {
        handleCommit(argc, argv);
    }

    else if (strcmp(argv[1], LOG) == 0) {
        handleLog(argc, argv);
    }

    else if (strcmp(argv[1], LOAD) == 0) {
        handleLoad(argc, argv);
    }

    freeIgnoreArr();
    
    return 0;
}