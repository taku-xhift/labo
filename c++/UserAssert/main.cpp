
#define NDEBUG

#include "Assert.hpp"

int main()
{
	int* integer;

	userAssert(integer, "assertion!!\n");

	printf("clear assertion\n");

	return 0;
}



