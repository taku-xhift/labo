


#include <iostream>

//#pragma comment(lib,"kernel32.lib")


void some_func(int i) {
	std::cout << __FUNCTION__ << "(" << i << ")" << std::endl;
}

template <typename T>
typename T::type* some_func(T t) {
	typename T::type variable_of_nested_type;
	std::cout << __FUNCTION__ << "(" << t << ")" << std::endl;
	return 0;
}

int main() {
	int i = 12;
	short s = 12;

	some_func(i);
	some_func(s);

	return 0;
}


