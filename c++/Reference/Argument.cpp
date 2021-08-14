


#include <iostream>


class Test {
public:
	int integer_;
};

void set(Test& test) throw() {
	test.integer_ = 4;
}

int main() {
	Test* test = new Test();
	set(*test);

	std::cout << test->integer_ << std::endl;
}

