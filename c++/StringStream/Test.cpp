


#include <iostream>
#include <sstream>
#include <string>


int main() {

	std::stringstream ss;
	ss << "test space" << __FUNCTION__ << 1 << true;
	std::string temp;

	while (ss >> temp);

	std::cout << temp;
}


