#include "repCheck.h"

i8 isRepCreated() {
    DIR* pRep = opendir(REP_NAME);

    if (pRep == NULL) {
        return 0;
    }

    closedir(pRep);

    return 1;
}