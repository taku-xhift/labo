


#include <iostream>


int main()
{
	bool result = false;
	result &= false;
	std::cerr << result << std::endl;

	result = false;
	result &= true;
	std::cerr << result << std::endl;

	result = true;
	result &= false;
	std::cerr << result << std::endl;

	result = true;
	result &= true;
	std::cerr << result << std::endl;
}


