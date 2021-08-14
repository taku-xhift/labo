
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



