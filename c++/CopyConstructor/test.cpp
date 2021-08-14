

#include <iostream>


class Base {
public:
	Base(int integer) throw() : integer_(integer) {}

	int integer_;
};


class Derived
	: public Base
{
public:
	Derived() throw()
		: Base(0)
	{
		
	}

	Derived(const Derived& other) throw()
		: Base(other.integer_)
	{
		
	}
};


int main() {
	Derived obj;
	obj.integer_ = 3;

	Derived copied(obj);

	std::cout << copied.integer_ << std::endl;
}

