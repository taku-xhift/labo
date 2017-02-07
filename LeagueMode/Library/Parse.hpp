/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.13 16:00:17
 *
 * @version 0.01, Shishido Takuya, 2010.04.13 16:00:17
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LeagueMode で使う例外クラスのベースクラス
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class ParseException : public ::std::exception
{
public:

	/**----------------------------------------------------
	 * @brief 例外文字列の取得
	 * @return  文字列の先頭ポインタ
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException



/**----------------------------------------------------
 * @brief Perl 側から受け取ったデータを解析する
 * @param[in]       reciprocateData_    Perl から受け取ったデータ
 * @return          reciprocateData_->type 型のデータを void* に変換したもの
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key, std::vector<int> node_ = std::vector<int>()) throw(ParseException);


#ifdef __cplusplus
}
#endif

#endif

