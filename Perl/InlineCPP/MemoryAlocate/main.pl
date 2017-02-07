
use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lalocate -lstdc++ -lgcc',
                            INC => '-I/lib/gcc/i686-pc-cygwin/3.4.4/include';
use Inline CPP => <<'END_OF_CPP';

#include <alocate.hpp>

void printer() {
    out();
}

END_OF_CPP

printer();


