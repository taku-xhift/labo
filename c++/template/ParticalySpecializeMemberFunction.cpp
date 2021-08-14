


#include <iostream>


template<int i, int j, typename Type>
struct Functor;


template<typename Type>
struct Functor<1,3, Type> {
	void operator()(const Type& type) const throw() {
		std::cout << 1 << ", " << 3 << std::endl;
		std::cout << type << std::endl;
	}
};


class Test {
public:

	template<int i, int j, typename Type>
	void print(const Type& type) const throw() {
		Functor<i, j, Type>()(type);
	}

};



int main() {
	Test test;
	test.print<1, 3, int>(0);
}


