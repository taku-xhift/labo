


#include <iostream>

template<typename Type1>
class Base {
public:
	virtual Type1 getValue() = 0;
};


class Child {//: public Base<int> {
public:
	typedef int Command;

	int value;
};

template<typename Type>
class Child2 : public Type
{
public:
	typedef typename Type::Command Command;

	Command getValue() {
		//return 1;
		return Command (3);
		//return a;
	}
};


int main() {
	Child2<Child> child2;
	std::cout << child2.getValue() << std::endl;
}


