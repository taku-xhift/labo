


#include <iostream>


class Test {
public:
	int integer_;
};


void print(const Test& test) throw() {
	std::cerr << test.integer_ << std::endl;
}

int main() {
	print(Test());
}
