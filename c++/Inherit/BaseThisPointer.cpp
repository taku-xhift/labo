


#include <iostream>
#include <typeinfo>


class Base;
class Derived;

template<typename Type>
void print(const Type& type) throw();
void save(Base* base) throw();
void save(Derived* derived) throw();


class Base {
public:

	Base() throw() {
		print(this);
		save(this);
	}

	virtual const char* name() const throw() { return "Base"; }
};


class Derived
	: public Base
{
public:
	Derived() throw() {
		print(this);
		save(this);
	}

	const char* name() const throw() { return "Derived"; }
};






Base* base_ = NULL;
Derived* derived_ = NULL;

template<typename Type>
void print(const Type& type) throw() {
	std::cout << typeid(Type).name() << std::endl;
}


void save(Base* base) throw() {
	base_ = base;
}
void save(Derived* derived) throw() {
	derived_ = derived;
}


int main() {
	Derived derived;

	std::cout << base_->name() << std::endl;
}


