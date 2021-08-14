
// •s‰Â”\

#include <iostream>

class Base {
public:
	static int create() = 0;
};

class Child
	: public Base
{
public:

	static int create() {
		return 3;
	}
};

int main() {
	std::cout << Child::create() << std::endl;
}


