


#include <boost/shared_ptr.hpp>
#include <iostream>

class Test
{
public:

	float Floating;

	Test()
	{
		this->Floating = 3.0f;
	}
};


class InhertenceTest : public Test
{
public:
	int integer;

	InhertenceTest()
	{
		this->integer = 3;
	}
};



void Out(boost::shared_ptr<Test> test)
{
	std::cout << test->Floating << std::endl;
}




int main()
{
	boost::shared_ptr<InhertenceTest> iTest(new InhertenceTest());

	Out(iTest);

	return 0;
}



