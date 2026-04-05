#include "commands\init.h"
#include "commands\add.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No command!\n");
        return 1;
    }

    if (strcmp(argv[1], INIT) == 0) {
        handleInit(argc, argv);
        return 0;
    }

    if (strcmp(argv[1], ADD) == 0) {
        handleAdd(argc, argv);
        return 0;
    }

    // if (strcmp(argv[1], "rm") == 0 && argc == 3) {
    //     handleCommit(argv[2]);
    // }
    
    return 0;
}