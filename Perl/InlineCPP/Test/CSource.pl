


use Inline C => <<'END_OF_CPP';

#include <stdio.h>


int greet() {
	printf("Hello World!\n");

	return 0;
}


END_OF_CPP

greet;

