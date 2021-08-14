

#include <iostream>

class Test {
public:
	Test(int integer_) : integer(integer_) {}

	const int integer;


	Test& operator=(Test& other_) {
		//this->integer = other_.integer;
		//return *this;
		return other_;
	}
};



int main() {
	Test test1(0);
	Test test2(4);
	test1 = test2;

	std::cout << test1.integer << std::endl;
}
