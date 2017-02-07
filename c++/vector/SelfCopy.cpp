


#include <iostream>
#include <vector>



int main() {
	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	container.insert(container.end(), container.begin(), container.end());

	for (std::vector<int>::const_iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}


