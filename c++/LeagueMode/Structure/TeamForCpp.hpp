/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.06 13:52:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.06 13:52:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED
#define LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "Team.h"


/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os         ストリームオブジェクト
 * @param[in]  team_      出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const Team& team_);


#endif

