

#include <iostream>
#include <string>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


/// C++/String/Count_If éQè∆
unsigned int count_if(const std::string& source, char target) {
	unsigned int counter = 0;

	std::string::size_type index = source.find(target);

	while (index != std::string::npos) {
		index = source.find(target, index +1);
		++counter;
	}

	return counter;
}



unsigned int count_field_of(const std::string& source) throw()
{
	const char doubleQuart = '\"';
	const char spliter = ',';

	unsigned int counter = 0;
	unsigned int doubleQuartNum = 0;
	std::string::size_type preIndex = 0;
	std::string::size_type nextIndex = source.find(spliter);

	while (nextIndex != std::string::npos)
	{
		//subStr = source.substr(preIndex, nextIndex-preIndex);
		std::string::const_iterator begin = source.begin();
		std::advance(begin, preIndex);
		std::string::const_iterator end = source.begin();
		std::advance(end, nextIndex);

		doubleQuartNum = std::count_if(begin, end, boost::lambda::_1 == doubleQuart);

		while ((doubleQuartNum % 2) != 0) {
			nextIndex = source.find(spliter, nextIndex + sizeof(spliter));
			end = source.begin();

			if (nextIndex == std::string::npos) {
				end = source.end();
				nextIndex = std::string::npos;
			} else {
				std::advance(end, nextIndex);
			}

			doubleQuartNum = std::count_if(begin, end, boost::lambda::_1 == doubleQuart);
		}

		if (nextIndex != std::string::npos) {
			preIndex = nextIndex + 1;       // 1 ÇÕ , ÇÃï∂éöêîï™
			nextIndex = source.find(spliter, preIndex);
		}
		++counter;
	}

	return counter;
}


int main() {
	std::string strings = "\"test\",\"sample\",\"st,ring,sample\"";

	std::cout << count_field_of(strings) << std::endl;
}

