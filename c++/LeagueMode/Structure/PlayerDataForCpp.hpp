
#ifndef LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED
#define LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "PlayerData.h"



/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  playerData_      出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const PlayerData& playerData_);


#endif

