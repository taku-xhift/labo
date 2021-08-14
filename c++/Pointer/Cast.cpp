

#include <iostream>


class A
{
public:
	A (){}
	virtual ~A (){}
};

class B
{
public:
	B (){};
	virtual ~B (){};
};

class C : public A, public B
{
public:
	C (){}
	virtual ~C (){}
};

int main()
{
	C* c = new C();
	A* a = c;
	B* b = c;

	printf("c:%p\n", c);
	printf("b:%p\n", b);
	printf("a:%p\n", a);

	delete c;
	return 0;
}
