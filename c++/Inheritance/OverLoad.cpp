

#include <iostream>
#include <typeinfo>

struct A {
	virtual void overload() throw() = 0;
};
struct B : public A {
	void print() throw() { std::cout << "B::print" << std::endl; }
};
struct C : public B {
	void overload() throw() {}
};



class CallBack {
public:
	CallBack(B* b) throw()
		: b_(b)
	{
		b->print();
		std::cout << typeid(this->b_).name() << std::endl;
	}

	B* b_;
	int integer_;
};

int main() {
	CallBack obj(new C());
	std::cout << obj.integer_ << std::endl;
}

