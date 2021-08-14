


#include <iostream>


template<typename Type, int integer>
class Test {
public:
	static const int number = integer;
	//typedef typename Type type;
	Type value_;
};


template<typename Type>
class Test<Type, 3> {
public:
	static const int number = 99;
};



int main() {
	std::cerr << Test<int, 3>::number << std::endl;
}

