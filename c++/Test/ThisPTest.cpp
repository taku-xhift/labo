

#include <iostream>

class Test;

//void output(const Test* test);
void output(Test* test);


class Test
{
public:
	float floating;

	Test()
		 : floating(3.0f)
	{
	}

	void out()
	{
		output(const_cast<Test*>(this));
	}


};


//void output(const Test* test)
void output(Test* test)
{
	std::cout << test->floating << std::endl;
}


int main()
{
	Test test;
	test.out();

	return 0;
}


