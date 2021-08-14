

#include <iostream>
#include <vector>
#include <algorithm>


struct Printer {
	void operator()(int integer_) {
		std::cout << integer_ << std::endl;
	}
};


int main() {
	std::vector<int> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	container.resize(5);

	std::for_each(container.begin(), container.end(), Printer());

	return 0;
}


