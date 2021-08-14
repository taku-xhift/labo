
#ifndef LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED
#define LEAGUEMODE_TEAMFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "Team.h"


/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @param[in]  os         �X�g���[���I�u�W�F�N�g
 * @param[in]  team_      �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const Team& team_);


#endif

