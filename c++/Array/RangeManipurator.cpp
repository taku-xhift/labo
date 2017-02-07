

#include <iostream>
#include <Personal/RangeManipulator.hpp>

const int size = 10;

int main() {
	int array[size];

	for (int i = 0; i < size; ++i) {
		array[i]  = i;
	}

	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << std::endl;
	}
}


