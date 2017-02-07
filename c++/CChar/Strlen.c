

#include <stdio.h>

int main()
{
	const char* name = "name";

	printf("%d\n", sizeof(name));
	printf("%d\n", strlen(name));

	const char* temp;
	memmove(temp, name, sizeof(name));

	printf("%s\n", temp);

	return 0;
}




