


#include <iostream>
#include <vector>

class Test {
	Test(int integer = 0, float floating = .0f) throw() {
		std::cout << "Test(int integer = 0, float floating = .0f) throw() {" << std::endl;
	}
	Test(int integer = 0, std::string strings = "") throw() {
		std::cout << "Test(int integer = 0, std::string strings = \"\") throw() {" << std::endl;
	}
};


int main()
{
	Test test();

	return 0;
}


