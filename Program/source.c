#include "dirCopy.h"
#include "userCommands.h"
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No command!\n");
        return 1;
    }

    if (strcmp(argv[1], SET) == 0) {
        optind = 2;

        int opt = getopt(argc, argv, "m:");
        if (opt == '?') {
            printf("Invalid usage!\n");
            return 1;
        }
        printf("REP : %s\n", optarg);
        setRepository(optarg);
    }

    if (strcmp(argv[1], COMMIT) == 0) {
    }
    
    return 0;
}