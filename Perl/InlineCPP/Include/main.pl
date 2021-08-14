use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 /cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/ -lmylib -lstdc++',
                            INC => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include';
#                            INC => '-I/D:/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/';
use Inline CPP => <<'END_OF_CPP';

#include <iostream>
#include "Include.hpp"

void hello() {
    sayHello("hello");
}

void world() {
    sayWorld("world");
}

END_OF_CPP

hello();
world();

