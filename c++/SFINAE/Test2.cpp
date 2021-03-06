

#include <iostream>
#include <boost/utility.hpp>
#include <boost/any.hpp>
#include <boost/static_assert.hpp>


#define STATIC_ASSERT(cond)        extern int assert_function(int [(cond)?1:-1])


using namespace std;


//! \brief メタプログラミング・判定用ライブラリ。
//! \note   is_class, has_xxx 等と SFINAE をうまく組み合わせるためのもの
//!         boost のものと同機能なので車輪の再開発です。
//!         肯定用
//! \author  Takuya Shishido
//! \date    2010.10.18 15:09:24
//! \version 0.01, Shishido Takuya, 2010.10.18 15:09:24
template<bool B, typename T = void>
struct enable_if_c {
	typedef T type;
};
template<typename T>
struct enable_if_c<false, T> {};

template<typename Cond, typename T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};



//! \brief メタプログラミング・判定用ライブラリ。
//!          is_class, has_xxx 等と SFINAE をうまく組み合わせるためのもの
//!          boost のものと同機能なので車輪の再開発です。
//!          否定用
//! \author  Takuya Shishido
//! \date    2010.10.18 15:09:24
//! \version 0.01, Shishido Takuya, 2010.10.18 15:09:24
template<bool B, typename T = void>
struct disable_if_c {
	typedef T type;
};

template<typename T>
struct disable_if_c<true, T> {};

template<typename Cond, typename T = void>
struct disable_if : public disable_if_c<Cond::value, T> {};


//! \brief requestDataType を typedef しているかどうかの判定用
//! \author  Takuya Shishido
//! \date    2010.10.18 15:09:24
//! \version 0.01, Shishido Takuya, 2010.10.18 15:09:24
template<typename T>
class has_requestDataType {
	typedef char yes;
	typedef struct { char a[2]; } no;

	template<typename U>
	static yes test(typename U::requestDataType*);

	template<typename U>
	static no test(...);
public:
	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};


//オーバーロードあり
template< typename T >
class has_setData_impl {

	typedef char yes_type ;
	typedef struct { char c[8]; } no_type ;

	template< typename U >
	static yes_type check( U *, void (U::*)(const typename T::requestDataType&) = &T::setData);


	template< typename U >
	static no_type check(...) ;
public:
	static const bool value = sizeof( check<T>( NULL ) ) == sizeof( yes_type ) ;
};


/*
    ★ 使い方
        １．Test のようにデータをセットしてもらいたい場合に
                その型を requestDataType として typedef する。
        ２．setData(Data& data_) 関数を準備する（Data& data_）の部分は任意。
                requestDataType& 型だと間違いはおきにくい
*/


class Data {
public:
	Data(int integer_ = 0) : integer(integer_) {}

	int integer;
};

class Data1 {
public:
	Data1(int integer_ = 0) : integer(integer_) {}

	int integer;
};


class Test {
public:
	typedef Data requestDataType;
	typedef Data1 requestDataType1;

	void setData(const requestDataType& data_) { this->data = data_; }
	void setData(const requestDataType1& data_) { this->data1 = data_; }

	requestDataType data;
	requestDataType1 data1;
};


//! \brief requestDataType を typedef している場合のクラス用のデータセット関数
//! \note   requestDataType が無い場合も別に定義してある
//              使い方は普通の関数と同じように２つ目まで引数にデータをセットしてやる
//! \param[in]  collector_  データをセットして欲しい方
//! \param[in]  data_       セットされるデータ
//! \retval     true        データはセットされた
//! \retval     false       boost::any_cast にて setData で期待されていた型への変換に失敗した
template <typename Collecter, typename Data>
bool setData(Collecter& collector_, Data& data_, typename enable_if<has_requestDataType<Collecter> >::type* = 0) {
	bool result = true;
	result = callSetData(collector_, data_);
	return result;
}


//! \brief requestDataType を typedef していないクラス用のデータセット関数
//! \note   何もしない
template <typename Collecter, typename Data>
bool setData(Collecter& collector_, Data& data_, typename boost::disable_if<has_requestDataType<Collecter> >::type* = 0) {
	bool result = true;
	cout << "No setData" << endl;
	return result;
}


// SetData がある場合呼ばれる
template<typename Collecter, typename Data>
bool callSetData(Collecter& collector_, typename Data data_,
				 typename boost::enable_if< has_setData_impl<Collecter> >::type* = 0 )
{
	cout << "enable_if" << endl;
	cout << __FUNCTION__ << endl;
	bool result = true;
	try {
		collector_.setData(boost::any_cast<Collecter::requestDataType>(data_));
	} catch (boost::bad_any_cast& ) {
		result = false;
	}
	return result;
}

class NoRequest {
public:
	//typedef int requestDataType;

	//void setData(const int& integer_) { this->integer = integer_; }

	NoRequest(int integer_ = 0) : integer(integer_) {}
	int integer;
};

int main() {
	Test test;
	Data data;
	NoRequest noRequest;

	setData(test, data);
	setData(noRequest, data);
}
