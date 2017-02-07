/**
 * @file  Tetra.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.10.31 21:19:42
 *
 * @version 0.01, Shishido Takuya, 2011.10.31 21:19:42
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_TETRA_HPP_INCLUDED
#define PM_MODE_TETRA_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
//#include "weCommonType.h"
typedef char weChar;
#include <ostream>


namespace pm_mode {


struct tetra
{
private:

	/****************************************************************
	 * @brief safebool イディオム用
	****************************************************************/
	struct dummy {
		void nonnull() {};
	};

	typedef void (dummy::*safe_bool)();

public:

	enum tetra_value {
		false_value,        //!< false の場合
		true_value,         //!< true の場合
		neither_value,      //!< どちらともいえない場合
		unknown_value,      //!< まだどちらかわからない場合
		max,
	};

	/****************************************************************
	 * @brief constructor
	 * @note    unexplicit
	 ***************************************************************/
	tetra(bool value) throw()
		: value_(value)
	{}

	/****************************************************************
	 * @brief constructor
	 * @note    unexplicit
	 ***************************************************************/
	tetra(tetra_value value) throw()
		: value_(static_cast<weChar>(value))
	{}

	/****************************************************************
	 * @brief safe_bool イディオム
	 * @note    http://ja.wikibooks.org/wiki/More_C%2B%2B_Idioms/%E5%AE%89%E5%85%A8%E3%81%AA_bool(Safe_bool)
	****************************************************************/
	operator safe_bool() const {
		return this->value_ == true_value? &dummy::nonnull : false;
	}


	/****************************************************************
	 * @brief ストリーム対応
	 ***************************************************************/
	friend std::ostream& operator<<(std::ostream& os, const tetra& value) {
		switch (value.value_) {
		case false_value:
			os << "false";
			break;
		case true_value:
			os << "true";
			break;
		case neither_value:
			os << "neither";
			break;
		case unknown_value:
		default:
			os << "unknown";
			break;
		}

		return os;
	}


	/****************************************************************
	 * @brief operator= とそのオーバーロード
	 ***************************************************************/
	tetra& operator=(const tetra& other) throw() {
		this->value_ = other.value_;
		return *this;
	}
	tetra& operator=(const tetra_value other) throw() {
		this->value_ = static_cast<weChar>(other);
		return *this;
	}
	tetra& operator=(bool other) throw() {
		this->value_ = other;
		return *this;
	}


	weChar value_;      //!< データ本体
};



/********************************************************************
 * @brief ! の定義
********************************************************************/
inline tetra operator!(tetra value)
{
	return value.value_ == tetra::false_value
		? tetra(true)
		: value.value_ == tetra::true_value
			? tetra(false)
			: tetra::neither_value;
}



/********************************************************************
 * @brief && の定義とそのオーバーロード
********************************************************************/
inline tetra operator&&(tetra x, tetra y)
{
	if (static_cast<bool>(!x) || static_cast<bool>(!y))
		return false;
	else if (static_cast<bool>(x) && static_cast<bool>(y))
		return true;
	else
		return tetra::neither_value;
}
inline tetra operator&&(tetra x, bool y) {
	return y? x : tetra(false);
}
inline tetra operator&&(bool x, tetra y) {
	return x? y : tetra(false);
}



/********************************************************************
 * @brief || の定義とそのオーバーロード
********************************************************************/
inline tetra operator||(tetra x, tetra y)
{
	if (static_cast<bool>(!x) && static_cast<bool>(!y))
		return false;
	else if (static_cast<bool>(x) || static_cast<bool>(y))
		return true;
	else
		return tetra::neither_value;
}
inline tetra operator||(tetra x, bool y) {
	return y? tetra(true) : x;
}
inline tetra operator||(bool x, tetra y) {
	return x? tetra(true) : y;
}


/********************************************************************
 * @brief == の定義とそのオーバーロード
********************************************************************/
inline tetra operator==(tetra x, tetra y) {
	return x.value_ == y.value_;
}
inline tetra operator==(tetra x, bool y) {
	return x == tetra(y);
}
inline tetra operator==(bool x, tetra y) {
	return tetra(x) == y;
}
inline tetra operator==(tetra::tetra_value value, tetra x) {
	return value == static_cast<tetra::tetra_value>(x.value_);
}
inline tetra operator==(tetra x, tetra::tetra_value value) {
	return value == static_cast<tetra::tetra_value>(x.value_);
}



/********************************************************************
 * @brief != の定義とそのオーバーロード
********************************************************************/
inline tetra operator!=(tetra x, tetra y) {
	return x.value_ != y.value_;
}
inline tetra operator!=(tetra x, bool y) {
	return x != tetra(y);
}
inline tetra operator!=(bool x, tetra y) {
	return tetra(x) != y;
}
inline tetra operator!=(tetra::tetra_value value, tetra x) {
	return value != static_cast<tetra::tetra_value>(x.value_);
}
inline tetra operator!=(tetra x, tetra::tetra_value value) {
	return static_cast<tetra::tetra_value>(x.value_) != value;
}


}    // namespace pm_mode



#endif





/********************************************************************
 * 以下、テストコード
********************************************************************/


#include <iostream>
#include <boost/lexical_cast.hpp>


int main() {
	using namespace pm_mode;
	using namespace std;

	tetra value1 = tetra::neither_value;
	tetra value2 = tetra::unknown_value;

	// これはコンパイルエラー
	//int i = value1;

	value1 = true;
	value1 = tetra::unknown_value;

	if (value1) {
		cout << "value1" << "\n";
		cout << (value1) << "\n";
	}
	if (!value1) {
		cout << "!value1" << "\n";
		cout << (!value1) << "\n";
	}
	if (value1 == tetra::neither_value) {
		cout << "value1 == tetra::neither_value" << "\n";
		cout << (value1 == tetra::neither_value) << "\n";
	}
	if (value1 == value2) {
		cout << "value1 == value2" << "\n";
		cout << (value1 == value2) << "\n";
	}
	if (value1 != value2) {
		cout << "value1 != value2" << "\n";
		cout << (value1 != value2) << "\n";
	}
	if (value1 && value2) {
		cout << "value1 && value2" << "\n";
		cout << (value1 && value2) << "\n";
	}
	if (value1 || value2) {
		cout << "value1 || value2" << "\n";
		cout << (value1 || value2) << "\n";
	}
}

