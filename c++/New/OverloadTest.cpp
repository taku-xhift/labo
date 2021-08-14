


#include <iostream>
#include <string>


void* operator new(size_t size)
{
	std::cout << "overload test" << std::endl;
	return malloc(size);
}

/*
class Test
{
public:

	int integer;

	Test()
		: integer(3)
	{
		
	}
};
*/


int main()
{
	int integer = 0;
	std::cout << integer << std::endl;

	std::string input;
	std::cin >> input;

	return 0;
}


