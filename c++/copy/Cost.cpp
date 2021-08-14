


#include <iostream>
#include <ctime>



class Test {
	int array[1000];
};



int main() {
	Test test[100];
	Test sub[100];

	std::clock_t start = std::clock();

	for (int i = 0; i < 100; ++i) {
		sub[i] = test[i];
	}

	float time = static_cast<float>(std::clock() - start)/CLOCKS_PER_SEC;

	std::cout << time << std::endl;
}


