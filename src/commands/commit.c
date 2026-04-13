#include "commands\commit.h"
#include "utils\repUtils.h"

#include "inclds.h"

void handleCommit(int argc, char** argv) {
    if (!isRepCreated()) {
        printNoRepError();
    }

    Config cfg;
    getConfig(&cfg);

    
}

i8 writeCData() {

}