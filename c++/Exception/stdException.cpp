


#include <iostream>
#include <string>

#define EXCEPTION_MESSAGE(message_)     std::string("Exception is thrown!!\nmessage: " + std::string(message_) + "\nfile: " + lexical_cast<string>(__FILE__) + "\nline: " + lexical_cast<string>(__LINE__) + "\n").c_str()


void thrower() throw(std::bad_alloc) {
	throw std::bad_alloc();
}


int main() {
	try {
		thrower();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		throw std::range_error(EXCEPTION_MESSAGE("message"));
	} catch (std::exception& e) {
		cerr << e.what() << endl;
	}
}

