
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <memory>

std::string input;


class Test
{
public:

	Test()
	{
		this->integer = 4;
		this->floating = 3.0f;
	}

	Test(int integer_, float floating_)
		: integer(integer_)
		, floating(floating_)
	{
	}

	int integer;
	float floating;
};


int main()
{
	std::shared_ptr<Test> test(new Test);
	{
		std::shared_ptr<Test> check = test;
		std::cout << check->floating << std::endl;
	}

	std::cin >> input;

	return 1;
}


