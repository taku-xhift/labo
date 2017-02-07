


#include <iostream>


int main()
{
	int array[2];
	array[0] = 1;
	array[1] = 2;

	try {
		std::cout << array[4] << std::endl;
		//array[3] = 3;
	} catch (...) {
		std::cout << "Catch a Exception" << std::endl;
	}

	return 0;
}


