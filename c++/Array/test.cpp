

#include <iostream>


struct Array {
	int array[10];
};


int main() {
	Array array;
	{
		Array arraySub;
		for (int i = 0; i < 10; ++i) {
			arraySub.array[i] = i;
		}

		array = arraySub;
	}

	for (int i = 0; i < 10; ++i) {
		std::cout << array.array[i] << std::endl;
	}
}


