


#include <iostream>
#include <deque>


int main() {
	std::deque<int> container;

	std::cout << container.size() << std::endl;
	try {
		std::cout << container.front() << std::endl;
	} catch (...) {
		std::cout << "catch" << std::endl;
	}
}


