#include <iostream>
#include <boost/shared_ptr.hpp>

class Real
{
public:
	float floa;
};

class Test
{
public:
	boost::shared_ptr<Real> real;
};



int main()
{
	Test test;
	{
		boost::shared_ptr<Real> real(new Real());
		real->floa = 1.0f;
		test.real = real;
	}

	std::cout << test.real->floa << std::endl;

	return 0;
}


