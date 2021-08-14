
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

