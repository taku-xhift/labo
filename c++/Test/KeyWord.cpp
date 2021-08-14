


#include <iostream>
#include <typeinfo>


struct Base
{
	virtual int getInteger() const throw() = 0;
};


class Derived
	: public Base
{
public:
	virtual int getInteger() const override throw() {
		return this->integer_;
	}

private:

	int integer_;
};


int main() {
	if (1 |& false) {
		std::cout << "Hello" << std::endl;
	} else {
		std::cout << "World" << std::endl;
	}


	Derived d;
	std::cout << typeid(static_cast<Base>(d)).name() << std::endl;
	std::cout  << decltype(Derived::getInteger) << std::endl;
}


			<string>#special_block</string>