use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 /cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/ -lmylib -lstdc++ -lMacro',
                            INC => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include';
#                            INC => '-I/D:/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/';
use Inline CPP => <<'END_OF_CPP';

#include <iostream>
#include "Macro.hpp"

HV* convertHash() {
    Test test;
    test.integer = 10;
//    {HV* hash = newHV();
//						  hv_store(hash, "key", strlen("key"), newSViv(test.integer), 0);
//        return hash;};
    createHash(test);
}

int getBiger() {
    getBig(1, 2);
}

END_OF_CPP


print convertHash->{'key'};
#print getBiger();
