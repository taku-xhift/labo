


#include <iostream>

class Test;

Test* makeTest()
{
	return new Test();
}


class Test
{
	friend makeTest();
	Test() {}

public:
	int integer;
};


int main()
{
	Test test = makeTest();

	std::cout << test.integer << std::endl;

	return 0;
}


