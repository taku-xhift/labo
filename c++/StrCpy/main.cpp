


#include <iostream>
#include <cstring>


int main()
{
	char character[0xff];
	strcpy(character, "sample");

	std::cout << character << std::endl;

	return 0;
}


