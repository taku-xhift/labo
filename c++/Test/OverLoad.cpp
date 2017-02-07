
#include <iostream>

class Test {
public:

	int integer() const throw() { return this->integer_; }
	void integer(int integer) { this->integer_ = integer; }

	int integer_;
};


int main() {
	Test test;
	test.integer(3);

	std::cout << test.integer() << std::endl;
}


