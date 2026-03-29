#include "dirCopy.h"
#include "userCommands.h"
#include "handleUser.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No command!\n");
        return 1;
    }

    if (strcmp(argv[1], INIT) == 0 && argc == 2) {
        handleInit();
    }

    if (strcmp(argv[1], ADD) == 0) {
        handleAdd(argc, argv);
    }
    
    return 0;
}