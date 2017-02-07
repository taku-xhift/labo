


#include <iostream>
#include <string>
#include <boost/cast.hpp>
#pragma comment(lib, "kernel32.lib")

class base1 {
public:
	virtual void print() {
		std::cout << "base1::print()" << std::endl;
	}

	virtual ~base1() {}
};

class base2 {
public:
	void only_base2() {
		std::cout << "base2::only_base2()" << std::endl;
	}
	virtual ~base2() {}
};


class derived : public base1, public base2 {
public:
	void print() {
		std::cout << "derived::print()" << std::endl;
	}
	void only_here() {
		std::cout << "derived::only_here()" << std::endl;
	}
	void only_base2() {
		std::cout << "‚¨‚Á‚ÆA‚±‚ê‚àI" << std::endl;
	}
};


class Test
{
public:
	void print() {
		std::cout << "Test::print()" << std::endl;
	}
};

int main()
{
	base1* p1 = new derived;
	p1->print();

	try {
		derived* pD = boost::polymorphic_cast<derived*>(p1);
		pD->only_here();
		pD->only_base2();

		Test* test = new Test;
		base2* pB = boost::polymorphic_cast<base2*>(test);
		//base2* pB = reinterpret_cast<base2*>(test);
		pB->only_base2();
	} catch (std::bad_cast& e) {
		std::cout << e.what() << std::endl;
	}

	delete p1;

	return 0;
}



