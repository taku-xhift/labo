


#include <iostream>
#include <typeinfo>

class Base {
	virtual void print() = 0;
};


class Derived
	: public Base
{
public:
	void print() throw() {
		std::cout << typeid(this).name() << std::endl;
	}
};


int main() {
	Derived derived;
	derived.print();
}

