

#include <iostream>
#include <cstring>


int main()
{
	const char* strings = "sample";

	//memcpy(strings, "test", sizeof("test"));
	//strcpy(strings, "test");
	strings = "test";

	std::cout << strings << std::endl;

	return 0;
}



