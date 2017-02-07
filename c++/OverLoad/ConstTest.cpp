


#include <iostream>

class Base {
public:
	virtual void print() const {
		std::cout << "Base" << std::endl;
	}
};

class Derived
	: public Base
{
public:

	void print() const {
		std::cout << "Derived" << std::endl;
	}
};

int main() {
	Base* derived = new Derived();
	derived->print();
}


