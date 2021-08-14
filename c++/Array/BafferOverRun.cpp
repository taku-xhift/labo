


#include <iostream>

int main() {
	int array[2];

	for (int i = 0; i < 2; ++i) {
		array[i] = i;
	}

	for (int i = 0; i < 2; ++i) {
		std::cout << array[i] << std::endl;
	}
	std::cout << array[3];

	return 0;
}


