


#include <deque>
#include <iostream>


int main() {
	std::deque<int> container;
	std::deque<int> sub;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	sub.swap(container);

	std::cout << "container" << std::endl;
	for (std::deque<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
	std::cout << "sub" << std::endl;
	for (std::deque<int>::iterator ite = sub.begin(); ite != sub.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}


