#include <iostream>
#include "VoidArray2.hpp"



int main()
{
	VoidArray voidArray;
	voidArray.voidData = 2.3f;

	std::cout << voidArray.value<char>() << std::endl;

	return 0;
}

