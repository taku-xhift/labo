#include <iostream>



class Test
{
public:
	Test()
	{
		this->floating = 2.0f;
	}

	~Test()
	{

	}

	float floating;
};


Test creation()
{
	return Test();
}


int main()
{
	Test test = creation();

	std::cout << test.floating << std::endl;

	return 0;
}

