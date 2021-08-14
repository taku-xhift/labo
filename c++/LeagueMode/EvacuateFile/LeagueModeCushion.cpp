
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "LeagueModeCushion.hpp"
#include "LeagueModeManager.hpp"


const char* leagueModeCushion()
{
	const char* name = LeagueMode::LeagueModeManager::getState();
	
	return name;
}



