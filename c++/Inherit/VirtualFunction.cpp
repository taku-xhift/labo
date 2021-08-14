


#include <iostream>

class Base {
public:
	void print() { std::cout << "Hello" << std::endl; }
};

class Child : public Base {
public:
	void print() { std::cout << "World" << std::endl; }
};

int main() {

	Base* child = new Child();

	child->print();

	return 0;
}


