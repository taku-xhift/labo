


#include <iostream>

struct BaseA {
	virtual void print() throw() = 0;
};


struct BaseB {
	virtual void print() throw() {}
};


struct MainImpl
	: public BaseB
{
	void print() throw() { std::cout << "MainImpl" << std::endl; }
};

struct MainUnImpl
	: public BaseB
{
	//void print() throw() { std::cout << "MainUnImpl" << std::endl; }
};


template<typename Type>
struct Object
	: public Type
{
	void print() throw() {
		Type::print();
	}
};

int main()
{
	Object<MainImpl> objImpl;
	objImpl.print();

	Object<MainUnImpl> objUnImpl;
	objUnImpl.print();
}


