


#include <iostream>

int main() {
	const char* data = "sample";

	std::cout << reinterpret_cast<unsigned int>(&data[0]) << std::endl;

	return 0;
}


