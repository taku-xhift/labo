#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf jb;

int main( int argc, char **argv ) {
    {
	int x = 777;
	if( setjmp( jb ) == 0 ) {
	    printf( "before: %p=%d\n", &argc, x );
	} else {
	    printf( "after : %p=%d\n", &argc, x );
	    exit(0);
	}
    }
    {
	int y = 666;
	longjmp( jb, 1 );
    }
}
