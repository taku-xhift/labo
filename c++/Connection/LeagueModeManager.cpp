/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "LeagueModeManager.hpp"


namespace {
	std::string nameManager = "My Name is LeagueModeManager!!";
}


namespace LeagueMode {


/**----------------------------------------------------
 * @brief constructor
 *----------------------------------------------------*/
LeagueModeManager::LeagueModeManager()
	: name(nameManager.c_str())
{
	for (int i = 0; i < 10; ++i) {
		this->intContainer.push_back(i);
	}
}


/**----------------------------------------------------
 * @brief  destructor
 *----------------------------------------------------*/
LeagueModeManager::~LeagueModeManager()
{
}

/**----------------------------------------------------
 * @brief   ŽÀsŠÖ”
 * @return  Œ»Ý‚Ìó‘Ô‚Ì–¼‘O
 *----------------------------------------------------*/
#if USE_STRING
std::string LeagueModeManager::run()
#else
const char* LeagueModeManager::run()
#endif
{
	return this->name;
}


std::vector<int> LeagueModeManager::getContainer()
{
	return this->intContainer;
}


}    // namespace LeagueMode

