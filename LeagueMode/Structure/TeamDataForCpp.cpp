
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @param[in]  os         �X�g���[���I�u�W�F�N�g
 * @param[in]  team_      �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const TeamData& teamData_)
{
	os << "TeamData Information" << std::endl;
	os << "name : " << teamData_.name << std::endl;
	os << "playerNumber : " << teamData_.playerNumber << std::endl;
	os << "playerData:" << std::endl;

	for (int i = 0; i < teamData_.playerNumber; ++i) {
		os << "player[" << i << "] : " << std::endl;
		os << teamData_.players[i] << std::endl;
	}

	return os;
}


