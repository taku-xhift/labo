#use Inline::Files;
use Inline C => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib';
use Inline C => <<'END_C';

#include "Include.h"

void greet() {
//    printf("Hello, world\n");
    printf("%s\n", getHello());
}
END_C

greet;
