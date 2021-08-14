#include <boost/shared_ptr.hpp>
#include <iostream>

class TestImpl
{
public:
	float floating;

	TestImpl() { floating = 3.0f; }

};



typedef boost::shared_ptr<TestImpl> SpTestImpl;



class Test
{
public:

	SpTestImpl spTestImpl;

	SpTestImpl getTest()
	{
		SpTestImpl test;
		return test;
	}

};







int main()
{
	Test test;

	SpTestImpl spTestImpl = test.getTest();


	std::cout << spTestImpl->floating << std::endl;

	return 0;

}

