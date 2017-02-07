


#include <iostream>
#include <vector>


int main() {
	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}


	std::vector<int>::iterator begin = container.begin();
//	for (int i = 0; i < 20; ++i) {
//		++begin;
//	}
	std::advance(begin, 20);

	for (std::vector<int>::iterator ite = begin; ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}


