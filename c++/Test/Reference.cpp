

#include <iostream>

int getter() throw() {
	return 4;
}


int main() {
	const int& integer = getter();

	std::cout << integer << std::endl;
}
