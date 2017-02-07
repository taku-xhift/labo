


#include <iostream>
#include <typeinfo>


template<typename Value>
struct GetType {
	typedef Value Type;
};


template<typename ValueType>
class Test {
public:
	typedef Test<ValueType> this_type;

	ValueType value_;
};


int main() {
	Test<int> test;

	std::cout << typeid(test).name() << std::endl;
}


