
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <sstream>
#include <string>
#include "LeagueModeCushion.hpp"
#include "LeagueModeManager.hpp"


#ifdef __cplusplus
extern "C" {
#endif

const char* leagueModeCushion()
{
#if USE_STRING
	//const char* name = LeagueMode::LeagueModeManager::getInstance().run().c_str();
#else
	//const char* name = LeagueMode::LeagueModeManager::getInstance().run();
#endif

	//std::string name;
	char name[0xff] = "";
	char all[0xff] = "";
	std::ostringstream os;

	for (int i = 0; i < LeagueMode::LeagueModeManager::getInstance().getContainer().size(); ++i) {
		//os << LeagueMode::LeagueModeManager::getInstance().getContainer().at(i) << std::endl;
		sprintf(name, "%d, ", LeagueMode::LeagueModeManager::getInstance().getContainer().at(i));
		strcat(all, name);
	}
	//name = os.str().c_str();

	std::string data = all;

	//return data.c_str();


	return LeagueMode::LeagueModeManager::getInstance().run();
}


#ifdef __cplusplus
}
#endif



