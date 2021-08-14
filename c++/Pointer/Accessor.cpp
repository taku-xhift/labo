


#include <iostream>
#include <vector>


int main() {
	std::vector<int>* container = new std::vector<int>();

	for (int i = 0; i < 10; ++i) {
		container->at(i) = i;
	}

	for (int i = 0; i < 10; ++i) {
		std::cout << (*container)[i] << std::endl;
	}
}


