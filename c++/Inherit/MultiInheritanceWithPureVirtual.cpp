


#include <iostream>


class Base1 {
public:
	virtual int getData() = 0;
};

class CoutView
	: public Base1
{
public:
	void print() {
		std::cout << this->getData() << std::endl;
	}
};


class CompositeData {
public:
	int data;
};


class Child
	: public CoutView
	, public CompositeData
{
public:

	int getData() {
		return this->data;
	}
};


int main() {
	Child child;
	child.data = 100;
	child.print();
}


