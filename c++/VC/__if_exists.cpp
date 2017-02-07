


#include <iostream>
#include <typeinfo>

class Test {
public:
	void print() {
		std::cout << typeid(Test).name() << std::endl;
	}
};

int main() {

	int integer = 0;

	__if_exists(integer::print) {
		std::cout << "exists" << std::endl;
	}

	Test test;

	__if_exists(test::print) {
		std::cout << "exists" << std::endl;
	}
}


