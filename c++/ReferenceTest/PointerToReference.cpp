


#include <iostream>


void out(int& integer_)
{
	std::cout << integer_ << std::endl;
}

int main()
{
	int* integer;

	out(integer);

	return 0;
}

