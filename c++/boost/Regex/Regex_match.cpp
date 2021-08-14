


#include <iostream>
#include <cassert>
#include <string>
#include <boost/regex.hpp>

//#pragma comment(lib, "libboost_regex-vc90-mt-s-1_42.lib")

int main()
{
	boost::regex reg("\\d{3}([a-zA-Z]+).(\\d{2}|N/A)\\s\\1");

	std::string correct = "123Hello N/A Hello";
	std::string incorrect = "123Hello 12 hello";

	assert(boost::regex_match(correct, reg) == true);
	assert(boost::regex_match(incorrect, reg) == true);

	return 0;
};


