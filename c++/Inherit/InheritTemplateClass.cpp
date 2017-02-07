


#include <iostream>

template<typename Type>
class Base {
public:
	Type type;
};

class Child
	: public Base<int>
{
public:
	int getData() { return this->type; }
};

int main() {
	Child child;
	child.type = 2;
	std::cout << child.getData() << std::endl;
}


