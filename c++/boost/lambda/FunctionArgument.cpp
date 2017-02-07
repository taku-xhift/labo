


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


struct Test {
	Test(int i) : integer_(i) {}
	int integer_;
};

void print(const Test& test) {
	std::cout << test.integer_ << std::endl;
}


int main() {
	using namespace boost::lambda;

	std::vector<Test> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	std::for_each(container.begin(), container.end(), bind(print, _1));
}


