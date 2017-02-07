


#include <iostream>
#include <algorithm>
#include <vector>


struct Test {
	Test(int integer) : integer_(integer) {}
	int integer_;

	//bool operator<(const Test& other) const throw() {
	//	return this->integer_ < other.integer_;
	//}
};

bool operator<(const Test& lhs, const Test& rhs) throw() {
	return lhs.integer_ < rhs.integer_;
}

struct Compare {
	bool operator()(const Test& lhs, const Test& rhs) {
		return lhs.integer_ < rhs.integer_;
	}
};

int main() {
	std::vector<Test> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(Test(i));
	}

	std::vector<Test>::const_iterator ite
		= std::lower_bound(container.begin(), container.end(), 3/*, Compare()*/);

	std::cout << (*ite).integer_ << std::endl;
}


