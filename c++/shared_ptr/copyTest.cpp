#include <iostream>
#include <boost/shared_ptr.hpp>

class Test
{
public:

	Test() : index(0) {};

	int index;

};




int main()
{
	Test test;
	test.index = 2;


	boost::shared_ptr<Test> spTest(new Test());

	*spTest = test;

	std::cout << spTest->index << std::endl;

	return 0;

}


