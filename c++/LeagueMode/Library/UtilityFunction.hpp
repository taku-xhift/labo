/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 19:35:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 19:35:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED
#define LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>

namespace LeagueMode {


/**----------------------------------------------------
 * @brief  stringstream を初期化する関数
 * @param[in]   ss_     初期化するストリーム
 *---------------------------------------------------*/
template<typename Type>
void clearStream(Type& ss_)
{
	// バッファクリア
	ss_.str("");
	// ストリームの状態をクリアする。この行がないと意図通りに動作しない
	ss_.clear(std::stringstream::goodbit);
}



/**----------------------------------------------------
 * @brief  stringstream を初期化する関数
 * @param[in]   ss_     初期化するストリーム
 *---------------------------------------------------*/
std::vector<std::string> splitString(std::string& string_);




}    // namespace LeagueMode

#endif

