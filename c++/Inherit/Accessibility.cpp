

#include <iostream>

class Base1 {
public:
	int getID() { return 0; }
};

class Base2 {
public:
};

class Base2Child
	: public Base2
{
public:
	void print() {
		std::cout << this->getID() << std::endl;
	}
};

class Child
	: public Base1
	, public Base2Child
{
public:
};


int main() {

	Child child;
	child.print();
}

