


#include <iostream>
#include <vector>


int main() {
	std::vector<int*> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(new int(i));
	}

	std::vector<int*> copied = container;

	for (std::vector<int*>::iterator ite = copied.begin(); ite != copied.end(); ++ite) {
		**ite += 1;
	}

	for (std::vector<int*>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << **ite << std::endl;
	}


	return 0;
}


