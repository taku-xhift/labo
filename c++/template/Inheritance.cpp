


#include <iostream>
#include <typeinfo>
#include <memory>

#define Print(parameter) std::cout << "PrintMacro => " << parameter << std::endl


template<int Channel>
class NULLType {
public:
	static const int channel = Channel;
	static void method() { Print(NULLType::channel); }
};


class Base {
public:
	virtual void method() = 0;
};

template<typename Policy1 = NULLType<4> >
class Child : public Base
			, public Policy1 {
public:
	void method() { this->Policy1::method(); }
};

class Cout_Print {
public:
	static const int channel = 1;
	//static void method() { std::cout << typeid(Cout_Print).name()<< std::endl; }
	static void method() { Print(Cout_Print::channel); }
};

class Test {
public:

	std::tr1::shared_ptr<Base> data;
};

int main() {
	Test test;
	//test.data.reset(new Child<Cout_Print>());
	test.data.reset(new Child<>());

	test.data->method();

	return 0;
}


