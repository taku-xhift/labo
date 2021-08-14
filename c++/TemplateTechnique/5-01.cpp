


#include <iostream>

struct Widget
{
	typedef int value_type;
};

template<typename T>
void something(typename T::value_type*)
{
	std::cout << "Having value_type!!" << std::endl;
}


template<typename T>
void something(...)
{
	std::cout << "Another." << std::endl;
}



int main()
{
	something<Widget>(0);
	something<int>(0);

	return 0;
};


