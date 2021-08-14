



#include <iostream>
#include <vector>
#include <algorithm>


class Sort {
public:
	bool operator()(int lhs, int rhs) throw(int) {
		if (lhs == 3) { throw lhs; }

		return lhs > rhs;
	}
};


int main() {
	std::vector<int> container;

	for (int i = 10; i > 0; --i) {
		container.push_back(i);
	}

	try {
		std::sort(container.begin(), container.end(), Sort());
	} catch (int&) {
		
	}

	for (std::vector<int>::const_iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}


