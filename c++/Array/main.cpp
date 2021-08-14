


#include <iostream>
#include <malloc.h>

#define ArraySizeOf(array)     (sizeof(array) / sizeof(array[0]))


int main()
{
	int* array = (int*)calloc(3, sizeof(int));

	std::cout << ArraySizeOf(*array) << std::endl;

	return 0;
}


