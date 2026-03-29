#include "repCheck.h"

i8 isRepCreated() {
    DIR* pRep = opendir(REP_NAME);

    if (pRep == NULL) {
        return 1;
    }

    return 0;
}