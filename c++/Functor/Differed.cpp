


#include <iostream>


template<typename ValueType>
class A {
public:
	A(const ValueType& value) : value_(value) {}

	bool operator()() const throw() {
		return (this->value_ == 0);
	}

	ValueType value_;
};


template<typename ValueType, template<typename> class Functor>
class B {
public:
	B(ValueType value) : value_(value), functor_(value_) {}

	void print() const throw() {
		if (this->functor_()) {
			std::cerr << "Hello" << std::endl;
		}
	}

public:
	ValueType           value_;
	Functor<ValueType>  functor_;
};


int main() {
	B<int, A> b(0);
	b.print();
}


