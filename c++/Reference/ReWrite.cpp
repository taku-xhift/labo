


#include <iostream>



int main() {

	int integer = 0;
	int& iR = integer;

	for (int i = 0; i < 10; ++i) {
		int integer = i;
		iR = integer;
		std::cout << iR << std::endl;
	}
}


