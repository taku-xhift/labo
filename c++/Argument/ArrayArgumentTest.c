


#include <stdio.h>


#define SIZE 8


void out(float[] array_, int size_)
{
	int i = 0;
	for (i = 0; i < size_; ++i) {
		printf("%f\n", array_[i]);
	}
}

int main()
{
	float array[SIZE];


	out(array, SIZE);


	return 0;
}


