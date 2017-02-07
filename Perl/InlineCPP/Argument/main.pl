
use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lLeagueMode -lstdc++ -lgcc',
                            INC => '-I/lib/gcc/i686-pc-cygwin/3.4.4/include';
use Inline CPP => <<'END_OF_CPP';

#include <iostream>

void useArgument(const char* name_) {
    //std::cout << name_ << std::endl;
    printf("%s\n", name_);
}

void printer() {
    useArgument("name_");
}

END_OF_CPP

#printer();
useArgument(42);


