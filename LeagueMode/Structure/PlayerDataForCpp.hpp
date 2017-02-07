/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.06 13:59:00
 *
 * @version 0.01, Shishido Takuya, 2010.04.06 13:59:00
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED
#define LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"



/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  playerData_      出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const PlayerData& playerData_);


#endif

