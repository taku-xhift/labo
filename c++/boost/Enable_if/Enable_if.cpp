


#include <iostream>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/has_xxx.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(type)



class some_class
{
public:
	typedef int type;
};


void some_func(int i) {
	std::cout << "void some_func(" << i << ")" << std::endl;
}

//template <typename T>
//void some_func(T t, typename boost::disable_if<boost::is_integral<T> >::type* p = 0)
//{
//	typename T::type variable_of_nested_type;
//	std::cout << "template <typename T> void some_func(T t)" << std::endl;
//}


template <typename T>
typename boost::enable_if<has_type<T> >::type some_func(T t) {
	typename T::type variable_of_nested_type;
	std::cout << "template <typename T> void some_func(T t)" << std::endl;
}


int main() {
	int i = 12;
	short s = 12;

	some_func(i);
	some_func(s);
	some_func(some_class());

	return 0;
}




