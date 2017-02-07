


#include <iostream>


class A {
	//friend template<typename Policy> class C;
//private:
protected:
	virtual int getID() const throw() { return 10; }
};

class B : public A {
public:
	virtual int getID() const throw() { return 20; }
};


template<typename Policy>
class C : public Policy {
public:
	void print() const throw() {
		std::cerr << this->A::getID() << std::endl;
	}
};


int main() {
	C<B> c;
	c.print();
	//B b;
	//b.print();
}

