


#include <iostream>

class A {
public:
	void print() const throw() { std::cerr << this->getID() << std::endl; }
	virtual int getID() const throw() = 0;
};


class B : public A{
public:
	int getID() const throw() { return 10; }
};


class C : public B {
public:
	int getID() const throw() { return 20; }
};


int main() {
	C c;
	c.print();
}


