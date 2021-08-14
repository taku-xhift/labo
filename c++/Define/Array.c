


#include <stdio.h>

typedef int weInt;
static const weInt size = 3;

int main()
{
	int i = 0;
	int array[size];

	for (i = 0; i < size; ++i) {
		array[i] = i;
	}

	for (i = 0; i < size; ++i) {
		printf("%d\n", array[i]);
	}

	return 0;
}


