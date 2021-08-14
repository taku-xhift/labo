

#include <iostream>
#include "alocate.hpp"


void out() {
	Test* test = new Test(3);
	std::cout << test->integer << std::endl;
	delete test;
//	std::cout << "Hello world!!" << std::endl;
}

