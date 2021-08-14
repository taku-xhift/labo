


#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


struct Test {
	Test(int i) : integer_(i) {}
	int integer_;
};


int main() {
	std::vector<Test> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(Test(i));
	}

	std::for_each(container.begin(), container.end(), std::cout << &boost::lambda::_1->*&Test::integer_);
}


