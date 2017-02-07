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
#include "LeagueModeCushion.hpp"
#include "LeagueModeManager.hpp"


const char* leagueModeCushion()
{
	const char* name = LeagueMode::LeagueModeManager::getState();
	
	return name;
}



