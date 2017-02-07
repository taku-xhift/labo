
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


unsigned int count_if(const std::string& source, const std::string& target) throw() {
	unsigned int counter = 0;
	std::string::size_type pos = source.find(target, 0);
	while (pos != std::string::npos) {
		++counter;
		pos = source.find(target, pos + target.size());
	}

	return counter;
}



void CSVReadLine(std::vector<std::string>& output, const std::string& source) throw()
{
	const std::string spliter = ",";
	const std::string doubleQuart = "\"";

	//std::string::size_type tempIndex = 0;
	std::string::size_type preIndex = 0;
	std::string::size_type nextIndex = source.find(spliter);
	std::string subStr = "";
	unsigned int doubleQuartNum = 0;

	while (nextIndex != std::string::npos) {
		//output.push_back(std::string());

		subStr = source.substr(preIndex, nextIndex-preIndex);
		doubleQuartNum = count_if(subStr, doubleQuart);

		if (doubleQuartNum == 1) {
			while ((doubleQuartNum % 2) != 0) {
				preIndex = nextIndex + 1;   // 1 ‚Í , ‚Ì•¶š”•ª
				nextIndex = source.find(spliter, preIndex);
				subStr += "," + source.substr(preIndex, nextIndex-preIndex);
				doubleQuartNum = count_if(subStr, doubleQuart);
			}
		}

		output.push_back(subStr);

		preIndex = nextIndex + 1;   // 1 ‚Í , ‚Ì•¶š”•ª
		nextIndex = source.find(spliter, preIndex);
	}

	output.push_back(source.substr(preIndex));
}

int main()
{
	std::string test = "test,\"1,2,3\",sample";
	//std::string target = "sample";

	//std::cout << count_if(test, target) << std::endl;

	std::vector<std::string> output;
	CSVReadLine(output, test);

	std::for_each(output.begin(), output.end(), std::cout << boost::lambda::_1 << "\n");
}
