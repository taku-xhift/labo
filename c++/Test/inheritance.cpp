

#include <iostream>
#include <typeinfo>


class TestBase
{
public:

	void out() { std::cout << typeid(TestBase).name() << std::endl; }

};



class Test : public TestBase
{
public:

	void out() { std::cout << "fdfd" << typeid(Test).name() << std::endl; }
};



int main()
{

	Test test;

	test.out();

	return 0;
}


