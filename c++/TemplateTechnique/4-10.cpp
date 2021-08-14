


#include <iostream>


template<typename T>
struct add_const
{
	typedef const T type;
};

template<typename T>
struct add_reference
{
	typedef T& type;
};


template<typename T>
struct add_reference<T&>
{
	typedef T& type;
};


template<typename T>
struct add_const_reference
{
	typedef
		typename add_const<typename add_reference<T>::type>::type
		type;
};


template<typename T>
struct remove_const
{
	typedef T type;
};


template<typename T>
struct remove_const<const T>
{
	typedef T type;
};




int main()
{

	int value = 3;
	add_const<int>::type c = value;
	add_reference<int>::type r = value;
	add_const_reference<int>::type cr = value;

	std::cout << c << std::endl;
	std::cout << r << std::endl;
	std::cout << cr << std::endl;


	return 0;
}




