
#ifndef LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED
#define LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"


/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os         ストリームオブジェクト
 * @param[in]  team_      出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const TeamData& teamData_);


#endif

