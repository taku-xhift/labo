


//#include <iostream>
#include <stdio.h>


void out(int integer_)
{
	++integer_;
	//std::cout << integer_ << std::endl;
	printf("integer_ = %d\n", integer_);
}

int main()
{
	int integer = 4;
	out(integer);

	//++integer;

	out(integer);

	return 0;
}


