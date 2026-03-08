#include "dirCopy.h"
#include "userCommands.h"
#include "handleUser.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No command!\n");
        return 1;
    }

    if (strcmp(argv[1], SET) == 0 && argc == 3) {
        handleSetRep(argv[2]);
    }

    if (strcmp(argv[1], COMMIT) == 0) {
    }
    
    return 0;
}