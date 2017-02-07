


#include <iostream>


int data = 0;

const int& getData()
{
	return data;
}


int main()
{
	int copy = getData();

	copy += 1;

	std::cout << copy << std::endl;
	std::cout << data << std::endl;

	return 0;
}


