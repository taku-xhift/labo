


#include <iostream>


struct A {
	A();
	struct B;
	B* b_;
};


template<typename Type>
void print(const Type& value) throw() {
	std::cout << value.b_->integer_ << std::endl;
}


struct A::B {
	int integer_;
};

A::A() throw() : b_(NULL) { this->b_ = new B(); }


int main() {
	A a;
}
