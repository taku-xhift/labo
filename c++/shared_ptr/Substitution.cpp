


#include <iostream>
#include <boost/shared_ptr.hpp>


class Test
{
public:
	float floating;

	Test()
	{
		this->floating = 3.0f;
	}

	~Test()
	{
		std::cout << "Destructed in Test." << std::endl;
	}
};


class Test2
{
public:
	int integer;
	Test test;

	~Test2()
	{
		std::cout << "Destructed in Test" << integer << "." << std::endl;
	}
};







int main()
{
	//Test2 test2;
	//{
	//Test2 test5;

	//test5.integer = 5;

	//test2 = test5;
	//}

	Test2 test2;
	Test test;

	test2.test = test;

	std::cout << test2.integer << std::endl;

	return 0;
}



