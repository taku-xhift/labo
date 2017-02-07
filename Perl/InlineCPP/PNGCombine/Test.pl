

use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/4.3.4 -lstdc++ -lpng -lgcc',
                            INC => '-I/lib/gcc/i686-pc-cygwin/4.3.4/include';
use Inline CPP => <<'END_OF_CPP';
#include <iostream>

int greet() {
	std::cout << "Hello World!" << std::endl;
}


END_OF_CPP

greet;
