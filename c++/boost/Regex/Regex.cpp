


//#include <boost/regex.hpp>
#include <regex>
#include <string>
#include <iostream>



int main() {
	std::string name = "string.png";
	std::tr1::smatch result;

	//::boost::regex pngExtension("*.png");
	//std::tr1::regex pngExtension(".*\.png");
	std::tr1::regex pngExtension("\.*.png");

	//if (::boost::regex_match(name, pngExtension)) {
	if (std::tr1::regex_match(name, result, pngExtension)) {
		std::cout << "name = " << name << std::endl;
		std::cout << "result = " << result.str() << std::endl;
	} else {
		std::cout << "not matched" << std::endl;
	}

	return 0;
}


