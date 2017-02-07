


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



class Data1 {
public:
	int integer;
};
class Data2 {
public:
	int integer;
};
//class Data1 {
//public:
//	int integer;
//};

class Test {
public:
	typedef Data1 value_type1;
	typedef Data2 value_type2;

	void setData(const Data1& data_) {
		this->data1 = data_;
	}

	void setData(const Data2& data_) {
		this->data2 = data_;
	}

	Data1 data1;
	Data2 data2;
};

using namespace std;

template<typename ValueType>
void setData(...) {
	cout << "setData(...)" << endl;
}


template<typename ValueType>
void setData(const ValueType& value_, typename ValueType::value_type1* = 0) {
	cout << "setData(typename ValueType::value_type1*)" << endl;
}

template<typename ValueType>
void setData(const ValueType& value_, typename boost::enable_if<has_xxx_impl<ValueType> >::value* = 0) {
	cout << "setData(typename &ValueType::setData)" << endl;
}

class X {
public:
	void xxx() {}
};

template< typename U , typename T >
static char check1( U *, void (U::*)(void) = &T::xxx ) ;

#include <typeinfo>

int main() {
	Test test;
	setData(test);

	bool temp = has_xxx_impl<Test>::value;
}


