/**
 * @file
 * @brief boost::any を参考に RTTI や boost library を使わずに実現したもの
 * @note       See http://www.boost.org/libs/any for Documentation.
 *
 * @author Takuya Shishido
 * @date   2010.10.18 15:54:46
 *
 * @version 0.01, Shishido Takuya, 2010.10.18 15:54:46
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#define Any_ALONETEST 1

#ifndef PM_WEO_TASK_ANY_HPP_INCLUDED
#define PM_WEO_TASK_ANY_HPP_INCLUDED


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <limits>
#include <assert.h>
//#include <type_traits>
#include <string>

#include "weoSpTypeInfo.h"
#include "weoTypeTraits.h"

#if (Any_ALONETEST == 1)
#include <iostream>
#else
#include "weDebug.h"
#include "weoLexicalCast.h"
#include "weoFlowException.h"
#endif


//-----------------------------------------------------
//  decralation
//-----------------------------------------------------
namespace pm_mode {
	class bad_any_cast;     //!< キャスト失敗を示すための例外クラス
}



#ifndef NEW
#define NEW new
#endif


namespace pm_mode {


//! brief 任意型データを保存するクラス
class Any
{
public:

	//! \brief constructor
	Any() throw()
		: content(NULL) {}

	//! \brief constructor
	//! \param[in]  value_  任意型のデータ
	template<typename ValueType>
	Any(const ValueType& value_) throw()
		: content(NEW Holder<ValueType>(value_))
	{
	}

	//! \brief constructor
	//! \param[in]  value_  任意型のデータ
	Any(const Any& other_) throw()
		: content(other_.content ? other_.content->clone() : NULL)
	{
	}

	//! \brief destructor
	~Any() throw() {
		if (this->content != NULL) {
			delete this->content;
			this->content = NULL;
		}
	}


	//! \brief もらった Any と自分のデータ入れ替え
	//! \param[in]  rhs_    入れ替え先
	Any& swap(Any& rhs_) throw() {
		std::swap(this->content, rhs_.content);
		return *this;
	}

	//! \brief operator = (データ本体と = でつなぐ)
	//! \param[in]  rhs_    入れ替え先
	template<typename ValueType>
	Any& operator=(const ValueType& rhs_) throw() {
		Any(rhs_).swap(*this);
		return *this;
	}

	//! \brief operator = (Any 型のデータとの =)
	//! \param[in]  rhs_    Any 型のデータ
	Any& operator=(Any rhs_) throw() {
		rhs_.swap(*this);
		return *this;
	}


	//! \brief データの有無のチェック
	//! \retval     true    有り
	//! \retval     false   無し
	bool empty() const throw()                              { return !this->content; }

	//! \brief 持っているデータの typeID を返す
	//! \return     型毎にユニークな ID。なければ ""
	const char* const typeName() const throw()              { return this->content ? this->content->name() : ""; }

	//! \breif cast して内部データを取得する
	//! \return    キャスト済みのデータ
	//! \except     bad_any_cast    template パラメータに指定された型に変換できない
	template<typename ValueType>
	const ValueType& getAs() const throw(bad_any_cast) {
		if (this->typeName() != typeid_of(ValueType).name()) {
			throw bad_any_cast(
#if (Any_ALONETEST == 0)
				std::string("Exception is thrown!!\nmessage: "
				    + std::string("bad_any_cast") + "\nfile: "
				    + ::pm_mode::lexical_cast<std::string>(__FILE__)
				    + "\nline: " + ::pm_mode::lexical_cast<std::string>(__LINE__)
				    + "\nfunction: " + ::pm_mode::lexical_cast<std::string>(__FUNCTION__)
				    + "\nmessage: MyType is " + this->typeName() + ", ValueType is " + typeid_of(ValueType).name()
				    + "\n")
#else
				""
#endif
				);
		}
		return static_cast<Holder<ValueType>*>(this->content)->held_;
	}

	//! \brief cast 済みのデータを取得する(渡したデータ型に自動で変換)
	//! \param[out] out_    データ出力先
	//! \retval     true    キャストし、格納出来た
	//! \retval     false   キャスト不可能だった
	template<typename ValueType>
	bool store(ValueType& out_) throw() {
		if (this->content.name() != typeid_of(ValueType).name()) {
			return false;
		}
		out_ = static_cast<Holder<ValueType>*>(this->content)->held_;
		return true;
	}


private:

	//! brief データホルダーのインターフェース型
	struct PlaceHolder
	{
		//! \brief destructor
		virtual ~PlaceHolder() {}

		//! \brief 持っているデータの型名を含んだ文字列を返す
		//! \return     型毎にユニークな名前。
		virtual const char* const name() const throw() = 0;

		//! \brief データのクローンを返す
		virtual PlaceHolder* clone() const throw() = 0;
	};

	//! \brief データホルダーの実装
	template<typename ValueType>
	class Holder
		: public PlaceHolder
	{
	public:

		//! \brief copy constructor
		explicit Holder(const ValueType& value_) throw()
			: held_(value_)
			, name_(typeid_of(ValueType).name())
		{
		}

		//! \brief 持っているデータの型名を含んだ文字列を返す
		//! \return     型毎にユニークな名前。
		virtual const char* const name() const throw() { return this->name_; }

		//! \brief データ本体のコピー
		//! \return     new した値
		virtual PlaceHolder* clone() const throw() {
			return NEW Holder(held_);
		}

	public:

		ValueType           held_;      //!< データ本体
		const char* const   name_;      //!< 格納しているデータの型名を含む名前

	private:
		//! \brief operator = の禁止
		Holder& operator=(const Holder&) throw();
	};

private:

	//! \brief cast 関数に対するデータの公開
	template<typename ValueType>
	friend ValueType* any_cast(Any*);

	PlaceHolder* content;   //!< 任意型を保存するためのデータホルダー
};


//! \brief キャスト失敗を示すための例外クラス
//! \note   循環参照になってしまうので、FlowException は継承できない
class bad_any_cast
//	: public task::FlowException
	: std::exception
{
public:

#if Any_ALONETEST
	const char* what() const throw() { return ""; }
#endif

	//! \brief constructor
	//! \param[in]  message_    error message
	explicit bad_any_cast(std::string message_ = "") throw()
#if (Any_ALONETEST == 1)
		: std::exception(message_.c_str()) {}
#else
		: task::FlowException(message_) {}
#endif
};


//! \brief Any 型からキャストするためのメソッド。ポインタ・non-const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
ValueType* any_cast(Any* operand_) throw () {
	return operand_ && (operand_->typeName() == typeid_of(ValueType).name())
	        ? &static_cast<Any::Holder<ValueType>*>(operand_->content)->held_ : NULL;
}

//! \brief Any 型からキャストするためのメソッド。ポインタ・const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
const ValueType* any_cast(const Any* operand_) throw () {
	return any_cast<ValueType>(const_cast<Any*>(operand_));
}

//! \brief Any 型からキャストするためのメソッド。リファレンス・non-const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
//! \except     bad_any_cast    template パラメータに指定された型に変換できない
template<typename ValueType>
ValueType any_cast(Any& operand_) throw (bad_any_cast) {
	typedef typename TypeTraits<ValueType>::ReferenceRemovedType nonref;
	nonref* result = any_cast<nonref>(&operand_);
	if(!result) {
		throw bad_any_cast(
#if (Any_ALONETEST == 0)
				std::string("Exception is thrown!!\nmessage: "
				    + std::string("bad_any_cast") + "\nfile: "
				    + ::pm_mode::lexical_cast<std::string>(__FILE__)
				    + "\nline: " + ::pm_mode::lexical_cast<std::string>(__LINE__)
				    + "\nfunction: " + ::pm_mode::lexical_cast<std::string>(__FUNCTION__)
				    + "\nmessage: MyType is " + this->typeName() + ", ValueType is " + typeid_of(ValueType).name()
				    + "\n")
#else
			""
#endif
			);
	}
	return *result;
}

//! \brief Any 型からキャストするためのメソッド。リファレンス・const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
//! \except     bad_any_cast    template パラメータに指定された型に変換できない
template<typename ValueType>
ValueType any_cast(const Any& operand_) throw (bad_any_cast) {
	typedef typename RemoveReference<ValueType>::type nonref;
	return any_cast<const nonref&>(const_cast<Any&>(operand_));
}


}   // namespace pm_mode



/*
//---------------------------------------------------------
// 使用例
//---------------------------------------------------------


class Sample {
public:

	static const unsigned int typeID = 0;       //!< 型ID

	//!< brief 型 ID を返す
	unsigned int dataTypeID() const { return Sample::typeID; }

	//! \brief constructor
	//! \param[in]  integer     データ
	Sample(int integer_ = std::numeric_limits<int>::max()) : integer(integer_) {}

	int integer;
};

int main()
{
	int count = 0;

	pm_mode::Any any = Sample(34);
	pm_mode::Any& anyArias = any;

	std::cout << ++count << " => " << pm_mode::any_cast<Sample>(any).integer << std::endl;
	std::cout << ++count << " => " << any.getAs<Sample>().integer << std::endl;
	std::cout << ++count << " => " << anyArias.getAs<Sample>().integer << std::endl;

	Sample sample = pm_mode::any_cast<Sample>(anyArias);
	std::cout << ++count << " => " << sample.integer << std::endl;

	Sample& sampleArias = sample;
	pm_mode::Any sampleArias_any = pm_mode::Any(sampleArias);
	std::cout << ++count << " => " << sampleArias_any.getAs<Sample>().integer << std::endl;
}




*/

#endif
