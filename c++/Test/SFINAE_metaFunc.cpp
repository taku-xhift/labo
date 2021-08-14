


#include <iostream>
#include <vector>

template<typename T>
class has_iterator
{
	typedef char yes;
	typedef struct { char a[2]; } no;

	template<typename C>
	static yes test(typename C::iterator*);

	template<typename C>
	static no test(...);

public:
	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};


int main()
{
	std::cerr << has_iterator<std::vector<int> >::value << std::endl;
	std::cerr << has_iterator<int>::value << std::endl;

	return 0;
}


