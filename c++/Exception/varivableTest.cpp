


#include <iostream>
#include <Exception>
#include <stdexcept>

const char* thrower() throw(std::bad_exception)
{
	return "Hello World";
}

int main()
{
	const char* greet;
	try {
		greet = thrower();
	} catch(...) {
		
	}

	std::cout << greet << std::endl;

	return 0;
}


