

#include <string>
#include <iostream>
#include <sstream>


int main() {
	int temp = 0;

	std::stringstream ss;

	ss << "1";
	ss << "3";
	ss >> temp;
	

	std::cout << temp << std::endl;
}

