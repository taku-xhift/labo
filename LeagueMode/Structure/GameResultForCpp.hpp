/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.07 15:08:09
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 15:08:09
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GAMERESULTFORCPP_HPP_INCLUDED
#define GAMERESULTFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/GameResult.h"

/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @note       ちょっと挙動が怪しいかも TODO
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  dataSet_         出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const GameResult& gameResult_);



#endif

