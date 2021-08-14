


#include <iostream>

class Base {
	
};

template<typename Type>
class Child
	: public Base {
public:

	Child(Type type_) : type(type_) {
		++Child::serialNumber;
	}

	Type type;

	static int serialNumber;
};

template<typename Type> int Child<Type>::serialNumber = 0;


int main() {
	int integer = 3;
	Child<int>(6);
	Child<double>(3.0);

	std::cout << Child<int>::serialNumber << std::endl;
}


