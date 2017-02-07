


#include <iostream>

class Test {
public:

	int integer;

	Test() : integer(8) {}
};

const Test& getTest() {
	return reinterpret_cast<const Test&>(new Test());
}

int main() {
	Test test = getTest();
	Test sample;
	std::cout << test.integer << std::endl;
}

