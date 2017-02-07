
#include <iostream>
#include <vector>
#include <algorithm>

class functor
{
public:

	template<typename Type>
	void operator() (const Type& data)
	{
		std::cout << data->integer << std::endl;
	}
};


class Test
{
public:

	int integer;
};


std::vector<Test> container;

int main()
{
	for (int i = 0; i < 10; ++i) {
		Test test;
		test.integer = i;
		container.push_back(test);
	}


	std::for_each(container.begin(), container.end(), functor());

	return 0;
}




