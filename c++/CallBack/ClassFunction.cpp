


#include <iostream>
#include <boost/any.hpp>


class Test {
public:

	void set(const int& integer) throw() {
		this->integer_ = integer;
	}

	int integer_;
};

class Base {
public:
	virtual ~Base() throw() {
		
	}


	virtual void operator()(const int& integer) throw() = 0;
};

template<typename ClassType, typename ValueType>
class Functor
	: public Base
{
public:
	typedef ClassType classType;
	typedef ValueType valueType;
	typedef void (ClassType::*Setter)(const ValueType&);

	Functor(ClassType* object, Setter setter) throw()
		: object_(object)
		, setter_(setter)
	{
		
	}

	void operator()(const int& integer) throw() {
		(object_->*setter_)(integer);
	}

	ClassType* object_;
	Setter setter_;
};



class Caller {
public:

	Caller() throw()
		: base_(NULL) {}


	template<typename ValueType>
	void operator()(const ValueType& value) throw() {
		(*this->base_)(value);
	}

	Base* base_;
};


int main() {
	Test* test = new Test();
	Caller caller;
	caller.base_ = new Functor<Test, int>(test, &Test::set);

	caller(3);

	std::cout << test->integer_ << std::endl;
}


