
#ifndef LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <vector>


//-----------------------------------------------------
//  define
//-----------------------------------------------------
#define USE_STRING 1


namespace LeagueMode {

/**
 * @brief ���[�O���Ǘ����邽�߂̃}�l�[�W���[
 *          
 * @author  Takuya Shishido
 * @date    2010.04.02 10:44:24
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 */
class LeagueModeManager
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *----------------------------------------------------*/
	LeagueModeManager();


	/**----------------------------------------------------
	 * @brief  destructor
	 *----------------------------------------------------*/
	~LeagueModeManager();


	/**----------------------------------------------------
	 * @brief   ���s�֐�
	 * @return  ���݂̏�Ԃ̖��O
	 *----------------------------------------------------*/
#if USE_STRING
	std::string& run();
#else
	const char* run();
#endif


	std::vector<int> getContainer();


	/**----------------------------------------------------
	 * @brief   �f�[�^�擾
	 *----------------------------------------------------*/
	static LeagueModeManager& getInstance() {
		static LeagueModeManager uniqueInstance;
		return uniqueInstance;
	}

private:

#if USE_STRING
	std::string name;   //!< ���O
#else
	const char* name;   //!< ���O
#endif


	std::vector<int>  intContainer;

};    // class LeagueModeManager

//LeagueMode::LeagueModeManager LeagueMode::LeagueModeManager::uniqueInstance;


}    // namespace LeagueMode

#endif

