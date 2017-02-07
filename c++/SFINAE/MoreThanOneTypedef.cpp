
// 参考
//http://lists.boost.org/Archives/boost/2002/03/27276.php


//! \brief メンバ関数チェッカー
//! \note   void setData(T t_) のような関数があれば value は true
template<typename T, typename U>
class has_setData_checker
{
	typedef char (&No)[1];      //!< No  用タグ
	typedef char (&Yes)[2];     //!< Yes 用タグ

	// 下の Yes No 判定用のヘルパー群。
	// これをはさまないと setData を持っていないクラスを渡すとコンパイルエラーが起きてしまう
	// setData を持っていないデータも渡してコンパイルできないと
	// 持っているクラスとそれ以外のクラスで処理の分岐が作れない
	template < typename T, typename U, void (T::*)(U) >         struct memberFunction1 {};
	template < typename T, typename U, void (T::*)(U*) >        struct memberFunciton2 {};
	template < typename T, typename U, void (T::*)(const U*) >  struct memberFunction3 {};
	template < typename T, typename U, void (T::*)(U&) >        struct memberFunction4 {};
	template < typename T, typename U, void (T::*)(const U&) >  struct memberFunction5 {};

	// 判定本体。関数宣言。
	// 上記の memberFunction 群一覧にある構造になっていれば Yes が、
	// そうでなければ No 型を返す関数になる。
	template< typename T, typename U > static No  has_setData_checker_helper(...);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction1< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunciton2< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction3< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction4< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction5< T,U,&T::setData >*);

public:
	// setData メンバ関数を持っていれば true が入っている
	static const bool value =
		sizeof(has_setData_checker_helper<T,U>(0)) == sizeof(Yes);
};

//
////! \brief メンバ関数チェッカー
////! \note   void setData(T t_) のような関数があれば value は true
//template<typename T>
//class has_setData_checker1
//{
//	typedef char (&No)[1];      //!< No  用タグ
//	typedef char (&Yes)[2];     //!< Yes 用タグ
//
//	// 下の Yes No 判定用のヘルパー群。
//	// これをはさまないと setData を持っていないクラスを渡すとコンパイルエラーが起きてしまう
//	// setData を持っていないデータも渡してコンパイルできないと
//	// 持っているクラスとそれ以外のクラスで処理の分岐が作れない
//	template < typename T, void (T::*)(...) >         struct memberFunction1 {};
//
//	// 判定本体。関数宣言。
//	// 上記の memberFunction 群一覧にある構造になっていれば Yes が、
//	// そうでなければ No 型を返す関数になる。
//	//template< typename T> static No  has_setData_checker_helper(...);
//	template< typename T> static Yes has_setData_checker_helper(memberFunction1< T,&T::setData >*);
//
//public:
//	// setData メンバ関数を持っていれば true が入っている
//	static const bool value =
//		sizeof(has_setData_checker_helper<T>(0)) == sizeof(Yes);
//};
#define STATIC_ASSERT(cond)        extern int assert_function(int [(cond)?1:-1])


#include <boost/utility/enable_if.hpp>

template<typename Collector, typename Data>
void setData(Collector& type_, Data& data, ...) {
	//STATIC_ASSERT((!has_setData_checker<Collector, Data>::value));
	__if_exists(Collector::setData) {
		STATIC_ASSERT((0));
	}
	cout << "setData With 0" << endl;
}


template<typename Collector, typename Data>
void setData(Collector& collector_, Data& data_,
			 typename boost::enable_if<has_setData_checker<Collector, typename Collector::requestDataType1> >::type* = 0, ...)
{
	cout << "setData With 1" << endl;
}

template<typename Collector, typename Data>
void setData(Collector& collector_, Data& data_,
			 typename boost::enable_if<has_setData_checker<Collector, typename Collector::requestDataType1> >::type* = 0,
			 typename boost::enable_if<has_setData_checker<Collector, typename Collector::requestDataType2> >::type* = 0, ...)
{
	cout << "setData With 2" << endl;
}




#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/any.hpp>

using namespace std;

struct Data1 {
};
struct Data2 {
};

struct Base {
	typedef Data1 requestDataType1;
	void setData(const requestDataType1& value_) {
		cout << "setData(requestDataType1 value_)" << endl;
	}
};

struct WithDefaultType {
	typedef Data1 requestDataType1;
	void setData(requestDataType1 value_) {
		cout << "setData(requestDataType1 value_)" << endl;
		this->value = value_;
	}
	Data1 value;
};

struct WithPointerType {
	typedef Data1 requestDataType1;
	void setData(requestDataType1* value_) {
		cout << "setData(requestDataType1* value_)" << endl;
		this->value = *value_;
	}
	Data1 value;
};

struct WithConstPointerType {
	typedef Data1 requestDataType1;
	void setData(const requestDataType1* value_) {
		cout << "setData(const requestDataType1* value_)" << endl;
		this->value = *value_;
	}
	Data1 value;
};

struct WithConstReferenceType {
	typedef Data1 requestDataType1;
	void setData(const requestDataType1& value_) {
		cout << "setData(const requestDataType1& value_)" << endl;
		this->value = value_;
	}
	Data1 value;
};

struct WithNoTypedef {
	void setData(const Data1& value_) {
		cout << "setData(const requestDataType1& value_)" << endl;
		this->value = value_;
	}
	Data1 value;
};

struct WithNo {
	Data1 value;
};

struct WithTwoTypedef {
	typedef Data1  requestDataType1;
	typedef Data2 requestDataType2;

	void setData(const Data1& value_) {
		cout << "setData(const requestDataType1& value_)" << endl;
		this->value = value_;
	}

	void setData(const Data2& value_) {
		cout << "setData(const requestDataType1& value_)" << endl;
		this->value2 = value_;
	}

	Data1 value;
	Data2 value2;
};

template<typename Type>
struct Delived
	: public Type
{

};


int main() {
	BOOST_STATIC_ASSERT((has_setData_checker<WithDefaultType, WithDefaultType::requestDataType1>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithPointerType, WithPointerType::requestDataType1>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstPointerType, WithConstPointerType::requestDataType1>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstReferenceType, WithConstReferenceType::requestDataType1>::value));

	//static const bool checker = has_setData_checker<WithConstReferenceType, typename WithConstReferenceType::requestDataType1>::value;
	//cout << "checker = " << checker << "\n" << endl;
	//cout << typeid(boost::enable_if<has_setData_checker<WithConstReferenceType, typename WithConstReferenceType::requestDataType1> >::type).name() << endl;


	//static const bool checkerWithNoTypedef = has_setData_checker<WithNoTypedef>::value;
	//cout << "checkerWithNoTypedef = " << checkerWithNoTypedef << "\n" << endl;



	WithConstReferenceType value;
	Data1 data;
	setData(value, data);

	WithNoTypedef noTypedef;
	Data2 data2;
	//setData(noTypedef, data2);

	WithTwoTypedef two;
	setData(two, data);

	WithNo no;
	setData(no, data);

	Delived<Base> delived;
	setData(delived, data);
}

