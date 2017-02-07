


#include <iostream>
#include <list>
#include <algorithm>

//std::list<int*> container;

int main()
{
	int* integer = new int;
	*integer = 3;

	{
		std::list<int*> container;
		container.push_back(integer);

		container.remove(integer);
	}

	std::cout << *integer << std::endl;
	delete integer;

	return 0;
}


