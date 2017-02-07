


#include <iostream>

const int size = 5;

void print(int array[size]) {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << std::endl;
		++array[i];
	}
}

int main() {
	int array[] = { 0, 1, 2, 3, 4 };

	print(array);

	std::cout << "test" << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << std::endl;
	}
}


