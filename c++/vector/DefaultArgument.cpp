


#include <iostream>
#include <vector>


void out(std::vector<int> container_ = std::vector<int>()) {
	for (std::vector<int>::iterator ite = container_.begin(); ite != container_.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}

int main() {

	std::vector<int> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}
	out();

	return 0;
}


