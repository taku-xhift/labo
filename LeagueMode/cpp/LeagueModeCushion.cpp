/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 12:54:34
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 12:54:34
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeCushion.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManager.hpp"


const char* leagueModeCushion()
{
	LeagueMode::LeagueModeManager::getInstance()->run();
	const char* name = LeagueMode::LeagueModeManager::getInstance()->getNowStateByString();

	if (strcmp(name, gameEnd) == 0) {
		LeagueMode::LeagueModeManager::destroyInstance();
	}

	return name;
}



