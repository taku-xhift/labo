
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
 * @brief   ���s�֐�
 * @return  ���݂̏�Ԃ̖��O
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

