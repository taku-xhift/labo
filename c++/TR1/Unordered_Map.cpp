


#include <iostream>
#include <unordered_map>


int main() {

	std::tr1::unordered_map<const char*, int> container;

	//container.insert(std::make_pair("test", 100));
	//container.insert(std::make_pair("sample", 600));
	//container.insert(std::make_pair("check", 400));
	container["sample"] = 600;

	for (std::tr1::unordered_map<const char*, int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << (*ite).first << " = " << ite->second << std::endl;
	}
}


