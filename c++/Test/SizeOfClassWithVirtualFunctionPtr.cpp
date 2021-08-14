


#include <iostream>
#include <cstdlib>


class Base {
public:
	virtual void print() const throw() = 0;
};


class Derived : public Base {
public:
	void print() const throw() {
		std::cerr << sizeof(Derived) << std::endl;
	}
};


int main() {
	Derived derived;
	memset(&derived, 0, sizeof(Derived));
	((Base*)&derived)->print();
}

