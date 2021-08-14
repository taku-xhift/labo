
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <sstream>
#include <limits>
#include <ctime>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManager.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManagerState.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Reciprocate.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/StreamObject.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Storage.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Converter.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/CommandCreater_FoundTeamData.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/DBError.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateDataForCpp.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int homeUserID = 0;
	const int awayUserID = 1;
}


//-----------------------------------------------------
//  using
//-----------------------------------------------------
using namespace so;



namespace LeagueMode {


//======================== Init ===================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]  manager_    GameManager's Instance
 * @param[in]  leagueWork_ Work Instance
 *---------------------------------------------------*/
InitState::InitState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
	// �����̏�����
    srand(static_cast<unsigned int>(time(NULL)));
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState InitState::run()
{
	//this->getManager().setState(MANAGERSTATE_TEAMSELECT);
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState InitState::getState() const
{
	return MANAGERSTATE_INIT;
}


//======================== TeamSelect =============================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
TeamSelectState::TeamSelectState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
	, step(STEP_FIRSTSTEP)
{
}

/**----------------------------------------------------
 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
 *---------------------------------------------------*/
void TeamSelectState::insertProcess()
{
	// �쐬���ꂽ���̂���������
	this->getManager().teamData.clear();

	// �`�[���ꗗ�̍쐬������
	std::vector<TeamData> container;
	for (int i = 0; i < TEAMLIST_MAX; ++i) {
		container.push_back(this->createTeamDataByName(i));
	}

	// ���ۂɕ\��
	std::cout << "TeamDataList :" << std::endl;
	for (int i = 0; i < TEAMLIST_MAX; ++i) {
		std::cout << i << ": " << container.at(i).name << std::endl;
	}

	this->step = STEP_FIRSTSTEP;
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState TeamSelectState::run()
{
	int selectNumber = std::numeric_limits<int>::max();

	if (!std::cin) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}

	switch (this->step) {
		case STEP_SELECTFIESTTEAM: {
			std::cout << "home ���A�g�p����`�[���̐�������͂��Ă�������" << std::endl;
			std::cin >> selectNumber;
			break;
		}
		case STEP_SELECTSECONDTEAM: {
			std::cout << "away ���A�g�p����`�[���̐�������͂��Ă�������" << std::endl;
			std::cin >> selectNumber;
			break;
		}
		default: {
			// �s���ȃX�e�b�v
			assert(0);
			break;
		}
	}

	// ���͂̉��
	if (selectNumber == std::numeric_limits<int>::max()) {
		std::cout << "���������������͂���Ȃ������悤�ł��B" << std::endl;
		return RUNSTATE_YET;
	}

	// �Q�[���I������
	if (selectNumber == TEAMLIST_INVALID) {
		//this->getManager().setState(MANAGERSTATE_RELEASE);
		return RUNSTATE_FINISH;
	}

	// �`�[�����쐬
	TeamData teamData;
	try {
		teamData = this->createTeamDataByName(selectNumber);
		std::cout << teamData.name << " ���w�肳��܂����B" << std::endl;
	} catch (BadSelectException&) {
		std::cout << "�����Ȕԍ����w�肳��܂����B�������l����͂��Ă�������" << std::endl;
		return RUNSTATE_YET;
	} catch (...) {
		// �����s���̗�O
		assert(0);
	}

	this->getManager().teamData.push_back(teamData);

	switch (this->getManager().teamData.size()) {
		case 0: {
			this->step = STEP_SELECTFIESTTEAM;
			break;
		}
		case 1: {
			this->step = STEP_SELECTSECONDTEAM;
			break;
		}
		case 2: {
			//this->getManager().setState(MANAGERSTATE_GETDATA);
			return RUNSTATE_FINISH;
			break;
		}
		default: {
			// �s���ȃX�e�b�v
			assert(0);
			return RUNSTATE_TROUBLE;
			break;
		}
	}

	return RUNSTATE_YET;
}


/**----------------------------------------------------
 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŌ�Ɏ��s�����
 *---------------------------------------------------*/
void TeamSelectState::releaseProcess()
{
	this->step = STEP_FIRSTSTEP;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState TeamSelectState::getState() const
{
	return MANAGERSTATE_TEAMSELECT;
}


/**----------------------------------------------------
 * @brief �I�����ꂽ�ԍ������Ƀ`�[���̖��O����ꂽ
 *          �`�[����Ԃ�
 * @param[in]   selectedNumber_     �I�����ꂽ�ԍ�
 * @return      ���������ɍ쐬���ꂽ Team
 *---------------------------------------------------*/
TeamData TeamSelectState::createTeamDataByName(int selectedNumber_) const throw(BadSelectException)
{
	TeamData teamData;

	switch (selectedNumber_) {
		case TEAMLIST_ARSENAL:
			strcpy(teamData.name, arsenal);
			break;
		case TEAMLIST_ASTONVILLA:
			strcpy(teamData.name, astonVilla);
			break;
		case TEAMLIST_BIRMINGHAMCITY:
			strcpy(teamData.name, birminghamCity);
			break;
		case TEAMLIST_BLACKBURNROVERS:
			strcpy(teamData.name, blackburnRovers);
			break;
		case TEAMLIST_BOLTONWANDERERS:
			strcpy(teamData.name, boltonWanderers);
			break;
		case TEAMLIST_BURNLEYFC:
			strcpy(teamData.name, burnleyFC);
			break;
		case TEAMLIST_CHERCY:
			strcpy(teamData.name, chercy);
			break;
		case TEAMLIST_EVERTON:
			strcpy(teamData.name, everton);
			break;
		case TEAMLIST_FULHAM:
			strcpy(teamData.name, fulham);
			break;
		case TEAMLIST_HULLCITY:
			strcpy(teamData.name, hullCity);
			break;
		case TEAMLIST_LIVERPOOLFC:
			strcpy(teamData.name, liverpoolFC);
			break;
		case TEAMLIST_MANCHESTERCITY:
			strcpy(teamData.name, manchesterCity);
			break;
		case TEAMLIST_MANCHESTERUNITED:
			strcpy(teamData.name, manchesterUnited);
			break;
		case TEAMLIST_PORTSMOUTH:
			strcpy(teamData.name, portsmouth);
			break;
		case TEAMLIST_STOKECITY:
			strcpy(teamData.name, stokeCity);
			break;
		case TEAMLIST_SUNDERLAND:
			strcpy(teamData.name, sunderland);
			break;
		case TEAMLIST_TOTTENHAMHOTSPUR:
			strcpy(teamData.name, tottenhamHotspur);
			break;
		case TEAMLIST_WESTHAMUNITED:
			strcpy(teamData.name, westHamUnited);
			break;
		case TEAMLIST_WIGANATHLETIC:
			strcpy(teamData.name, wiganAthletic);
			break;
		case TEAMLIST_WOLVERHAMPTONWANDERERS:
			strcpy(teamData.name, wolverhamptonWanderers);
			break;
		case TEAMLIST_INVALID:
			strcpy(teamData.name, gameEnd);
			break;
		case TEAMLIST_MAX:
			// �� through down
		default:
			throw BadSelectException();
			break;
	}

	return teamData;
}


//======================== GetData ================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
GetDataState::GetDataState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
}



/**----------------------------------------------------
 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
 *---------------------------------------------------*/
void GetDataState::insertProcess()
{
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState GetDataState::run()
{
	// home ���̃f�[�^�̃Z�b�g
/*
	ReciprocateData* reciprocateData = reinterpret_cast<ReciprocateData*>(calloc(1, sizeof(ReciprocateData)));
	findPlayerData_by_TeamDataName(this->getManager().teamData.at(home).name, reciprocateData);
	this->getManager().teamData.at(home) = convertToTeamData(reciprocateData);
	releaseReciprocateData(reciprocateData);
*/
	{
		FoundTeamDataDirection direction = getFoundTeamDataDirection();
		//direction.teamName = this->getManager().teamData.at(home).name;
		setTeanName_FoundTeamDataDirection(&direction, this->getManager().teamData.at(home).name);
		ReciprocateData* command = commandCreate_FoundTeamData(&direction);
		DBError error = findPlayerDataByTeamName(command, &(this->getManager().teamData.at(home)));
		releaseReciprocateData(command);
	}


	// away ���̃f�[�^�̃Z�b�g
/*
	reciprocateData = reinterpret_cast<ReciprocateData*>(calloc(1, sizeof(ReciprocateData)));
	findPlayerData_by_TeamDataName(this->getManager().teamData.at(away).name, reciprocateData);
	this->getManager().teamData.at(away) = convertToTeamData(reciprocateData);
	releaseReciprocateData(reciprocateData);
*/
	{
		FoundTeamDataDirection direction = getFoundTeamDataDirection();
		//direction.teamName = this->getManager().teamData.at(away).name;
		setTeanName_FoundTeamDataDirection(&direction, this->getManager().teamData.at(away).name);
		ReciprocateData* command = commandCreate_FoundTeamData(&direction);
		DBError error = findPlayerDataByTeamName(command, &(this->getManager().teamData.at(away)));
		releaseReciprocateData(command);
	}


	out << "�K�v�ȂQ�`�[���̃`�[�������擾����" << endl;
	out << "home : " << manchesterUnited << ", away : " << chercy << endl;

	out << "�`�[����� : " << endl;
	out << "home : " << endl;
	out << this->getManager().teamData.at(home) << endl;
	out << "away : " << endl;
	out << this->getManager().teamData.at(away) << endl;

	//this->getManager().setState(MANAGERSTATE_GAME);
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState GetDataState::getState() const
{
	return MANAGERSTATE_GETDATA;
}


//======================== Game ===================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
GameState::GameState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
}


/**----------------------------------------------------
 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
 *---------------------------------------------------*/
void GameState::insertProcess()
{
	this->getManager().gameResult.clear();
}



/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState GameState::run()
{
	out << "TeamData " << this->getManager().teamData.at(home).name <<
		" and " << this->getManager().teamData.at(away).name << " is Game in Europe." << endl;

	int homeOffence = getTeamOffence(&this->getManager().teamData.at(home));
	int homeDefence = getTeamDefence(&this->getManager().teamData.at(home));
	int awayDefence = getTeamDefence(&this->getManager().teamData.at(away));
/*
	// �f�[�^�̏�����
	for (int i = 0; i < homeAwayMax; ++i) {
		GameResult result;
		int offence = getTeamOffence(&this->getManager().teamData.at(i));
		out << i << ": " << endl;
		out << "TeamOffence : " << offence << endl;

		strcpy(result.name, this->getManager().teamData.at(i).name);
		result.time = gameStartTime;

		// �S�[�����̌v�Z
		if (offence > 2000) {
			result.score = 3;
		} else if (offence > 1800) {
			result.score = 2;
		} else {
			result.score = 1;
		}
		this->getManager().gameResult.push_back(result);
	}

	// ���т̐f�f
	if (this->getManager().gameResult.at(home).score == this->getManager().gameResult.at(away).score) {
		// �Ǝ��v�Z���B���قǈӖ��͂Ȃ��B
		int winner = homeOffence - awayDefence - (awayDefence - homeDefence);
		if (winner > 0) {
			this->getManager().gameResult.at(home).victory = GAMERESULTCATEGORY_PKWIN;
			this->getManager().gameResult.at(away).victory = GAMERESULTCATEGORY_PKLOSE;
		} else {
			this->getManager().gameResult.at(home).victory = GAMERESULTCATEGORY_PKLOSE;
			this->getManager().gameResult.at(away).victory = GAMERESULTCATEGORY_PKWIN;
		}
	} else if (this->getManager().gameResult.at(home).score > this->getManager().gameResult.at(away).score) {
			this->getManager().gameResult.at(home).victory = GAMERESULTCATEGORY_WIN;
			this->getManager().gameResult.at(away).victory = GAMERESULTCATEGORY_LOSE;
	} else if (this->getManager().gameResult.at(home).score < this->getManager().gameResult.at(away).score) {
			this->getManager().gameResult.at(home).victory = GAMERESULTCATEGORY_LOSE;
			this->getManager().gameResult.at(away).victory = GAMERESULTCATEGORY_WIN;
	} else {
		assert(0);
	}
*/
	//this->getManager().setState(MANAGERSTATE_RESULT);
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState GameState::getState() const
{
	return MANAGERSTATE_GAME;
}


//======================== Result =================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
ResultState::ResultState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState ResultState::run()
{
	//out << this->getManager().messageForNext << endl;
	//out << this->getManager().gameResult.at(home) << endl;
	//out << this->getManager().gameResult.at(away) << endl;

	//sendGameResult(homeUserID, &this->getManager().gameResult.at(home));
	//sendGameResult(awayUserID, &this->getManager().gameResult.at(away));

	//this->getManager().setState(MANAGERSTATE_TEAMSELECT);
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState ResultState::getState() const
{
	return MANAGERSTATE_RESULT;
}


//======================== Release ================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
ReleaseState::ReleaseState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState ReleaseState::run()
{
	//this->getManager().setState(MANAGERSTATE_END);
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState ReleaseState::getState() const
{
	return MANAGERSTATE_RELEASE;
}



//======================== END ====================================================================
/**----------------------------------------------------
 * @brief      constructor
 * @param[in]   manager_    LeagueModeManager's Instance
 * @param[in]   leagueWork_ Work Instance
 *---------------------------------------------------*/
EndState::EndState(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
	: StateBase(leagueModeManager_, leagueWork_)
{
}


/**----------------------------------------------------
 * @brief  ���C��
 * @return  �������
 *---------------------------------------------------*/
RunState EndState::run()
{
	return RUNSTATE_FINISH;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
 * @return  ��Ԃ̖��O�B
 *---------------------------------------------------*/
ManagerState EndState::getState() const
{
	return MANAGERSTATE_END;
}



}    // namespace LeagueMode

