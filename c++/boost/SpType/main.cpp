/**
 * @file
 * @brief RTTI 無しで型チェックするための機構
 * @note    boost 参考。
 *
 * @author Takuya Shishido
 * @date   2010.11.09 16:31:56
 *
 * @version 0.01, Shishido Takuya, 2010.11.09 16:31:56
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <functional>


//-----------------------------------------------------
//  define
//-----------------------------------------------------

//! \brief 型情報を取得する。使用例は一番下。
//! \note   name() 等のアクセス方法は type_info と変わらない
//! \note   下のクラス定義などはこれを使うための物なのでこの define だけ知ってれば充分
//! \return sp_typeinfo 型で、
//!             typeid_of(Type).name() で クラス名を "含む" 文字列。
//!             具体的な内容はコンパイラの __FUNCTION__ による。
#define typeid_of(...) (::pm_mode::sp_typeid_<__VA_ARGS__ >::typeinfo)
#define VA_ARGTEST(...) (__VA_ARGS__)





namespace pm_mode {


//! \brief type_info クラスに変わる型情報クラス
class sp_typeinfo
{
public:

	//! \brief constructor
	//! \param[in]  name    クラス名
	explicit sp_typeinfo(const char* const name) throw()
		: name_(name)
	{
	}

	//! \brief operator == (同値判定)
	bool operator==(sp_typeinfo const& rhs) const throw() {
		return (this == &rhs);
	}

	//! \brief operator != (不一致判定)
	bool operator!=(sp_typeinfo const& rhs) const throw() {
		return (this != &rhs);
	}

	//! \brief 派生関係はこれを使用して調べる
	//! \note   type_info にインターフェースをあわせてある
	bool before(sp_typeinfo const& rhs) const throw() {
		return std::less< sp_typeinfo const* >()(this, &rhs);
	}

	//! \brief 名前取得
	const char* name() const throw()        { return this->name_; }

private:

	//! \brief copy constructor の禁止
	sp_typeinfo(sp_typeinfo const&);
	//! \brief 代入の禁止
	sp_typeinfo& operator=(sp_typeinfo const&);

	const char* const name_;      //!< 型に関する名前
};

//! \brief 指定された型の名前を生成する
//! \note   型ごとにユニークな ID を生成する方法の核心
//              template で指定された型は __FUNCTION__ の情報に含まれるので
//              クラスごとのユニークな名前が生成できる。
//              しかしその内容はコンパイラ依存(__FUNCTION__ による)。
template<typename T> struct sp_typeid_
{
	//! \brief 名前を取得する
	//! \note
	//! \return     template に指定された型の名前を含む文字列
	static const char* const name() {
		return __FUNCTION__;
	}

	static sp_typeinfo typeinfo;    //!< 型情報格納先。ヘッダにオブジェクトを置くためのテクニック。
};


//! \brief グローバルに作る型の情報を含むオブジェクト
//! \note   Any 型に格納した種類分だけオブジェクトが生成される。
template<typename Type> sp_typeinfo sp_typeid_<Type>::typeinfo(sp_typeid_<Type>::name());


//! \brief 以下、template の特殊化
template<typename Type> struct sp_typeid_<Type&>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type const>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type volatile>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type const volatile>
	: sp_typeid_<Type>
{
};


}    // namespace pm_mode




template<typename ValueType>
class Test {
public:
	ValueType integer;
};


int main() {
	std::cout << typeid_of(Test<int>).name() << std::endl;
	//std::cout << VA_ARGTEST(Test<int>) << std::endl;
}

