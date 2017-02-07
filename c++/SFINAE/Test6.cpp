
#include <iostream>
#include <boost/static_assert.hpp>


//! \brief メンバ関数チェッカー
//! \note   void setData(T t_) のような関数があれば value は true
template<typename T, typename U>
class has_setData_checker {
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
	// 上記の memberFunction 群一覧にある構造になっていれば Yes が。
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

using namespace std;

struct Data {
};

struct WithDefaultType {
	typedef Data requestDataType;
	void setData(requestDataType value_) {
		cout << "setData(requestDataType value_)" << endl;
		this->value = value_;
	}
	Data value;
};

struct WithPointerType {
	typedef Data requestDataType;
	void setData(requestDataType* value_) {
		cout << "setData(requestDataType* value_)" << endl;
		this->value = *value_;
	}
	Data value;
};

struct WithConstPointerType {
	typedef Data requestDataType;
	void setData(const requestDataType* value_) {
		cout << "setData(const requestDataType* value_)" << endl;
		this->value = *value_;
	}
	Data value;
};

struct WithConstReferenceType {
	typedef Data requestDataType;
	void setData(const requestDataType& value_) {
		cout << "setData(const requestDataType& value_)" << endl;
		this->value = value_;
	}
	Data value;
};





int main() {
	BOOST_STATIC_ASSERT((has_setData_checker<WithDefaultType, WithDefaultType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithPointerType, WithPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstPointerType, WithConstPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstReferenceType, WithConstReferenceType::requestDataType>::value));

	//their their_;
	//their_.setData(her());
}

