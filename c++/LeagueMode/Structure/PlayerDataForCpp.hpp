
#ifndef LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED
#define LEAGUEMODE_PLAYERDATAFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "PlayerData.h"



/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @param[in]  os               �X�g���[���I�u�W�F�N�g
 * @param[in]  playerData_      �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const PlayerData& playerData_);


#endif

