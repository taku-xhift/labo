


#include <iostream>

template<typename Type>
void out() {
	std::cout << sizeof(Type) << std::endl;
}

int main()
{
	out<int>();

	return 0;
}


