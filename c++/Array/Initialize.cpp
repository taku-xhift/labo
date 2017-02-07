

#include <iostream>
#include <vector>

struct Array {
	int array_[3];
	//std::vector<int> array_[3];
};

const Array array[] = {
	{1, 2, 3},
	{2, 3},
};


int main() {
	for (int i = 0; i < 3; ++i) {
		std::cerr << array[0].array_[i] << std::endl;
		std::cerr << array[1].array_[i] << std::endl;
	}


	int arrayOf3[3] = {3};
	std::cerr << "arrayOf3\n";
	for (int i = 0; i < 3; ++i) {
		std::cerr << arrayOf3[i] << std::endl;
	}
}


