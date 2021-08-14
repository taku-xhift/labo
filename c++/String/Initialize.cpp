


#include <iostream>
#include <string>

class Struct {
public:
	const char* strings;
};


int main() {
	Struct structure;
	structure.strings = '\0';

	std::cout << structure.strings << std::endl;

	return 0;
}


