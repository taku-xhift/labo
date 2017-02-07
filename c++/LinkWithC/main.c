
#include <stdio.h>
#include "Test.h"

int main()
{
	struct Data* data;
	data = test();


	printf("Hello World!!\n");

	printf("DataClass\n");
	printf("power => %d\n", data->power);
	printf("diffence => %d\n", data->diffence);
	printf("balance => %d\n", data->balance);

	return 0;
}


