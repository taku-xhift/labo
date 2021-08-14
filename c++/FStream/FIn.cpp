


#include <iostream>
//#include <fstream>
#include <string>


int main() {
	//std::string strings = "sample Strings";
	const char* strings = "sample Strings";

	//std::ifstream ifs;
	std::stringstream ifs;
	ifs << strings;

	std::string output;
	std::getline(ifs, output);
	std::cout << output << std::endl;
}


