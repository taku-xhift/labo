

#include <iostream>

struct Test {
	Test() : integer_(0) {}
	int integer_;
};

void reset(Test*& test) {
	std::cerr << "test address => " << test << std::endl;

	test = new Test();
}


int main() {
	Test* test = NULL;
	reset(test);
	test->integer_ = 4;

	std::cout << test->integer_ << std::endl;
}

