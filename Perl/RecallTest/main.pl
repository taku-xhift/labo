use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lstdc++',
                            INC => '-I/lib/gcc/i686-pc-cygwin/3.4.4/include',
                            ENABLE => STD_IOSTREAM;
use Inline CPP => <<'END_OF_CPP';

void exceptionThrower(const char* field_, const char* team_) throw(std::exception) {
    std::cout << __FILE__ << std::endl;
    std::cout << __LINE__ << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    std::cout << field_ << std::endl;
    std::cout << team_ << std::endl;
    throw std::exception();
}

void functionName() {
    try {
        exceptionThrower("field_","team_");
    } catch (...) {
        std::cout << "some exception catch!!" << std::endl;
    }
}

END_OF_CPP

#exceptionThrower
functionName

