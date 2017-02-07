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

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os         ストリームオブジェクト
 * @param[in]  team_      出力オブジェクト
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


