/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.07 18:18:08
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_LEAGUEMODEEXCEPTION_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEEXCEPTION_HPP_INCLUDED


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <exception>


namespace LeagueMode {

/**
 * @brief LeagueMode で使う例外クラスのベースクラス
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class LeagueModeException : public ::std::exception
{
public:

	/**----------------------------------------------------
	 * @brief 例外文字列の取得
	 * @return  文字列の先頭ポインタ
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException


/**
 * @brief 本来選択されるはずが無かったものを選択した場合に投げられる例外
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class BadSelectException : public LeagueModeException
{
public:

	/**----------------------------------------------------
	 * @brief 例外文字列の取得
	 * @return  文字列の先頭ポインタ
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException
}    // namespace LeagueMode

#endif

