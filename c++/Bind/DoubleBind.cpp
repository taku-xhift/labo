


#include <iostream>
#include <functional>


void out(int first, int second) {
	std::cout << first << second << std::endl;
}


int main()
{
	std::bind1st(out, 2);

	return 0;
}


