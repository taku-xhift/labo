


#include <iostream>
#include <boost/shared_ptr.hpp>
#include <algorithm>


class Foo
{
public:

	Foo(int _x) : x(_x)
	{
	}

	~Foo()
	{
		std::cout << "Destructing a Foo with x = " << x << std::endl;
	}

	int x;
};


typedef boost::shared_ptr<Foo> SpFoo;

class SpFooOps
{
	bool operator()(const SpFoo &a, const SpFoo &b)
	{
		return a->x > b->x;
	}

	void operator()(const SpFoo &a)
	{
		std::cout << a->x << std::endl;
	}
};



int main()
{
	SpFoo spFoo(new Foo(2));




	return 0;
}


