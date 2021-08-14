


#include <iostream>

template<int X, int N>
struct pow
{
	static const int value = X * pow<X, N-1>::value;
};


template <int X>
struct pow<X, 0>
{
	static const int value = 1;
};

int main()
{
	int result = pow<2, 3>::value;

	std::cout << result << std::endl;

	return 0;
}


