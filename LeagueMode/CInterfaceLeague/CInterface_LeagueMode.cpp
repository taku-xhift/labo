/**
 * @file
 * @brief �O���ďo���p���W���[���B
 * @note    ����� Perl �Ȃ�ŌĂяo���Ă��炤�ƁA
 *              ��ʂ�̍�Ƃ� c++ �ōs����B
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/CInterfaceLeague/CInterface_LeagueMode.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManager.hpp"



/**----------------------------------------------------
 * @brief LeagueMode �� �`�[���Z���N�g�Ɋւ��鏈���S��
 *----------------------------------------------------*/
void LeagueMode_TeamSelect()
{
	LeagueMode::LeagueModeManager::executeModule(LeagueMode::LEAGUEMODEMANAGERBEHAVIOR_TEAMSELECT);
	//LeagueMode::LeagueModeManager::destroyInstance();
}



/**----------------------------------------------------
 * @brief LeagueMode �� �������ʂ̏o�͂Ɋւ��鏈���S��
 *----------------------------------------------------*/
void LeagueMode_AutoGame(const char* homeTeam_, const char* awayTeam_)
{
	//TODO
	//::LeagueMode::LeagueModeManager::executeModule(LeagueMode::LEAGUEMODEMANAGERBEHAVIOR_AUTOGAME);
	::LeagueMode::LeagueModeManager::behaviorGame(homeTeam_, awayTeam_);
	::LeagueMode::LeagueModeManager::destroyInstance();
}




