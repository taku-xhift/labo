


#include <iostream>

template<int N>
struct factorial
{
	static const int value = N * factorial<N - 1>::value;
};

template<>
struct factorial<0>
{
	static const int value = 1;
};


int main()
{
	int result = factorial<3>::value;

	std::cout << result << std::endl;

	return 0;
}


