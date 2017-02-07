use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib -lstdc++',
                            INC => '-I/lib/gcc/i686-pc-cygwin/3.4.4/include',
#                            INC => '-I/D:/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/';
                            ENABLE => STD_IOSTREAM;
use Inline CPP => <<'END_OF_CPP';

template<typename Type> int getSize() {
    return sizeof(Type);
}

void printSize() {
    std::cout << getSize<int>() << std::endl;
}

END_OF_CPP

printSize();

