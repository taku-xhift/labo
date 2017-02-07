


#include <iostream>
#include <vector>

void array(int* array) throw() {
	for (int i = 0; i < 10; ++i) {
		std::cout << array[i] << std::endl;
	}
}


int main() {
	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	array(&container[0]);
}


