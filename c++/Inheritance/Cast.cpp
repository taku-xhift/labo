

#include <iostream>
#include <typeinfo>


class Base {
public:
	void printer() {
		std::cerr << typeid(Base).name() << std::endl;
	}
};


class Derived : public Base {
public:
	void print() {
		Base& base = *this;
		base.printer();
	}
};


int main() {
	Derived derived;
	derived.print();
}



