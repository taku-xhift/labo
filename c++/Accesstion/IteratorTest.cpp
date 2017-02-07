

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>


class Test
{
public:

	float floating;

	Test()
	{
		this->floating = 3.0f;
	}
};
typedef boost::shared_ptr<Test> SpTest;

std::vector<Test> testArray;
std::vector<SpTest> spTestArray;

void Out(Test test)
{
	std::cout << test.floating << std::endl;
}



int main()
{
	for (int i = 0; i < 10; ++i) {
		SpTest test(new Test());
		testArray.push_back(test);
	}

	Out(testArray[0]);

	return 0;
}


