

package CAPI;

use Inline C => <<'END_OF_CPP';

#include <stdlib.h>

HV* createHash() {
    HV* hash = newHV();
    hv_store(hash, "key", strlen("key"), newSViv(4), 0);

    return hash;
}

END_OF_CPP


return 1;
