

#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> split(const std::string& strings_, char sepalator_ = ',') {
	std::string sorce = strings_;
	std::vector<std::string> container;
	std::string temp;

	std::string::size_type result = sorce.rfind(sepalator_);
	while (result != std::string::npos) {
		container.push_back(sorce.substr(result+1));
		sorce.resize(result);
		result = sorce.rfind(sepalator_);
	}
	container.push_back(sorce);

	return std::vector<std::string> (container.rbegin(), container.rend());
}


int main() {
	char str[0xff];
	strcpy(str, "sample");

	std::string string(str);

	std::cout << str << std::endl;
	std::cout << string << std::endl;

	std::string::size_type lastof = string.find_last_of('z');
	std::cout << "lastof:" << lastof << std::endl;

	std::string::size_type rfind = string.rfind('a');
	std::cout << "rfind:" << rfind << std::endl;

	std::vector<std::string> splitString = split("sample;test;result", ';');

	for (std::vector<std::string>::iterator ite = splitString.begin(); ite != splitString.end(); ++ite) {
		std::cout << *ite << std::endl;
	}

	return 0;
}

