


#include <iostream>

struct Test {
	const int array_[3];
};


int main() {
	Test test;
	int array[3];
	for (int i = 0; i < 3; ++i) {
		array[i] = i;
	}

	//memcpy(test.array, array, sizeof(int)*3);

	for (int i = 0; i < 3; ++i) {
		std::cout << test.array_[i] << std::endl;
	}
}

