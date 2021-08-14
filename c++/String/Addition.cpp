

#include <iostream>
#include <string>

std::string getString() throw() {
	return std::string("test") + "sample";
}

int main() {
	std::string string = getString();

	std::cerr << string << std::endl;
}
