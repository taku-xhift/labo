


#include <iostream>
#include <map>
#include <string>





int main() {
	std::map<std::string, int> map;
	map["test"] = 2;

	std::map<std::string, int>::const_iterator ite = map.find("test");
	if (ite != map.end()) {
		std::cout << ite->second << std::endl;
	}
}


