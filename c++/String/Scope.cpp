

#include <iostream>

int main() {

	const char* name = "";
	unsigned int address = 0;

	{
		std::string data = "name";
		name = data.c_str();
		address = (unsigned int)data.c_str();
	}

	std::cout << name << std::endl;
	std::cout << "address = " << address << std::endl;
	std::cout << (const char*)address << std::endl;

	return 0;
}

