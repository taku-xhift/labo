


#include <iostream>


template<typename Derived>
struct Base {

	Base() {
//		static_cast<Derived*>(this)->implementation();
	}

//	virtual void implementation() const {
//		std::cout << "struct Base" << std::endl;
//		std::cout << __FUNCTION__ << std::endl;
//	}
	virtual void implementation() const = 0;
};


struct Derived
	: Base<Derived>
{
	void implementation() const {
		std::cout << "struct Derived" << std::endl;
		std::cout << __FUNCTION__ << std::endl;
	}
};


int main() {
	Derived obj;

	obj.implementation();

	return 0;
}

