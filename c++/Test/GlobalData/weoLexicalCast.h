/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.12.06 16:13:08
 *
 * @version 0.01, Shishido Takuya, 2010.12.06 16:13:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_TASK_WEOLEXICALCAST_HPP_INCLUDED
#define PM_MODE_TASK_WEOLEXICALCAST_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>


namespace pm_mode {


//====  lexical_auto_cast  ==========================================

//! \brief 型を指定すると文字列と数字型をキャストする
//! \param[in]  from_   元のデータ
//! \tparam     To      変換後の型
//! \tparam     From    返還前の型
//! \return     キャストされたデータ
template<typename To, typename From>
To lexical_cast(const From& from) throw() {
//	To result;
//	std::stringstream ss;
//
//	ss << from;
//	ss >> result;
//
//	return result;
	return boost::lexical_cast<To>(from);
}

//! \brief lexical_auto_cast のためのタグクラス
//! \note   仕組みは、型変換 operator を使って変換先の型推論を行い
//              その情報を使って pm_mode::lexical_cast するだけ。
template<typename From>
class lexical_cast_t
{
private:
	const From& from_;      //!< 変換前のデータ
public:

	//! \brief constructor
	//! \param[in]  from_   変換前のデータ
	explicit lexical_cast_t(const From& from) throw()
		: from_(from)
	{
	}

	//! \brief cast operator
	//! \return キャスト後のデータ
	template<typename To>
	operator To() const throw() {
		return lexical_cast<To>(this->from);
	}
};


//! \brief 型推論を行い引数を自動的に型変換するキャスト
//! \param[in]  from_   元のデータ
//! \return     キャスト後のデータ
template<typename From>
lexical_cast_t<From> lexical_auto_cast(From from) throw() {
	return lexical_cast_t<From>(from);
}


}    // namespace pm_mode


#endif

