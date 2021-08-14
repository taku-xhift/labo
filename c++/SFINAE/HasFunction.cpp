// 参考 http://cpplover.blogspot.com/2008/10/hasxxx.html

#include <iostream>
#include <boost/utility/enable_if.hpp>

//オーバーロードあり
template< typename T >
class has_xxx_impl {

	typedef char yes_type ;
	typedef struct { char c[8]; } no_type ;

	template< typename U >
	static yes_type check( U *, void (U::*)(void) = &T::xxx ) ;


	template< typename U >
	static no_type check(...) ;
public:
	static const bool value = sizeof( check<T>( NULL ) ) == sizeof( yes_type ) ;
};

//オーバーロードなし
//template < typename T, int T::* > struct sfinae_helper { typedef void type ; } ;
//
//template < typename T, typename U = void >
//struct has_xxx_impl
//{
//	static bool const value = false ;
//};
//
//template< typename T>
//struct has_xxx_impl< T, typename sfinae_helper< T, &T::xxx >::type >
//{
//	static bool const value = true ;
//};

using namespace std;

template<typename T>
void callXXX(T& test_,
			 typename boost::enable_if< has_xxx_impl<T> >::type* =0 )
{
	cout << "callXXX" << endl;
	test_.xxx();
}

class Test {
public:
	void xxx() { std::cout << "xxx" << std::endl; }
};

class Sample {
public:
	void xyz() {}
};


int main() {
	callXXX(Test());
	callXXX(Sample());
}

