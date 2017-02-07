/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 13:44:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 13:44:12
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <sstream>
#include <limits>
#include <ctime>
#include "LeagueModeManager.hpp"
#include "LeagueModeManagerState.hpp"
#include "StreamObject.hpp"
#include "Team.h"
#include "TeamForCpp.hpp"
#include "LeagueModeDefineData.h"
#include "ReciprocateDataForCpp.hpp"
#include "MemoryLeakCheck.hpp"
#include "Reciprocate.h"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int homeUserID = 0;
	const int awayUserID = 1;

	const int home = 0;
	const int away = 1;
	const int homeAwayMax = 2;
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
    srand(static_cast<unsigned int>(time(NULL)));       /* 乱数の初期化 */
}


/**----------------------------------------------------
 * @brief  メイン
 *---------------------------------------------------*/
void InitState::run()
{
	this->getManager().setState(MANAGERSTATE_TEAMSELECT);
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
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
 * @brief 状態が変更されたときに最初に実行される
 *---------------------------------------------------*/
void TeamSelectState::insertProcess()
{
	// 作成されたものを消去する
	this->getManager().teamData.clear();

	// チーム一覧の作成をする
	std::vector<Team> container;
	for (int i = 0; i < TEAMLIST_MAX; ++i) {
		container.push_back(this->createTeamByName(i));
	}

	// 実際に表示
	std::cout << "TeamList :" << std::endl;
	for (int i = 0; i < TEAMLIST_MAX; ++i) {
		std::cout << i << ": " << container.at(i).name << std::endl;
	}

	this->step = STEP_FIRSTSTEP;
}


/**----------------------------------------------------
 * @brief  メイン
 *---------------------------------------------------*/
void TeamSelectState::run()
{
	int selectNumber = std::numeric_limits<int>::max();
	if (!std::cin) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}

	switch (this->step) {
		case STEP_SELECTFIESTTEAM: {
			std::cout << "home 側、使用するチームの数字を入力してください" << std::endl;
			std::cin >> selectNumber;
			break;
		}
		case STEP_SELECTSECONDTEAM: {
			std::cout << "away 側、使用するチームの数字を入力してください" << std::endl;
			std::cin >> selectNumber;
			break;
		}
		default: {
			// 不明なステップ
			assert(0);
			break;
		}
	}

	// 入力の解析
	if (selectNumber == std::numeric_limits<int>::max()) {
		std::cout << "正しい数字が入力されなかったようです。" << std::endl;
		return;
	}

	Team team;

	try {
		team = this->createTeamByName(selectNumber);
		std::cout << team.name << " が指定されました。" << std::endl;
	} catch (BadSelectException&) {
		std::cout << "無効な番号が指定されました。正しい値を入力してください" << std::endl;
		return;
	} catch (...) {
		// 原因不明の例外
		assert(0);
	}

	this->getManager().teamData.push_back(team);

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
			this->getManager().setState(MANAGERSTATE_GETDATA);
			break;
		}
		default: {
			// 不明なステップ
			assert(0);
			break;
		}
	}
}


/**----------------------------------------------------
 * @brief 状態が変更されたときに最後に実行される
 *---------------------------------------------------*/
void TeamSelectState::releaseProcess()
{
	this->step = STEP_FIRSTSTEP;
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
 *---------------------------------------------------*/
ManagerState TeamSelectState::getState() const
{
	return MANAGERSTATE_TEAMSELECT;
}


/**----------------------------------------------------
 * @brief 選択された番号を元にチームの名前を入れた
 *          チームを返す
 * @param[in]   selectedNumber_     選択された番号
 * @return      引数を元に作成された Team
 *---------------------------------------------------*/
Team TeamSelectState::createTeamByName(int selectedNumber_) const throw(BadSelectException)
{
	Team team;

	switch (selectedNumber_) {
		case TEAMLIST_ARSENAL:
			strcpy(team.name, arsenal);
			break;
		case TEAMLIST_ASTONVILLA:
			strcpy(team.name, astonVilla);
			break;
		case TEAMLIST_BIRMINGHAMCITY:
			strcpy(team.name, birminghamCity);
			break;
		case TEAMLIST_BLACKBURNROVERS:
			strcpy(team.name, blackburnRovers);
			break;
		case TEAMLIST_BOLTONWANDERERS:
			strcpy(team.name, boltonWanderers);
			break;
		case TEAMLIST_BURNLEYFC:
			strcpy(team.name, burnleyFC);
			break;
		case TEAMLIST_CHERCY:
			strcpy(team.name, chercy);
			break;
		case TEAMLIST_EVERTON:
			strcpy(team.name, everton);
			break;
		case TEAMLIST_FULHAM:
			strcpy(team.name, fulham);
			break;
		case TEAMLIST_HULLCITY:
			strcpy(team.name, hullCity);
			break;
		case TEAMLIST_LIVERPOOLFC:
			strcpy(team.name, liverpoolFC);
			break;
		case TEAMLIST_MANCHESTERCITY:
			strcpy(team.name, manchesterCity);
			break;
		case TEAMLIST_MANCHESTERUNITED:
			strcpy(team.name, manchesterUnited);
			break;
		case TEAMLIST_MAX:
			// ↓ throuth down
		default:
			throw BadSelectException();
			break;
	}

	return team;
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
 * @brief 状態が変更されたときに最初に実行される
 *---------------------------------------------------*/
void GetDataState::insertProcess()
{
}


/**----------------------------------------------------
 * @brief  メイン
 *---------------------------------------------------*/
void GetDataState::run()
{
	ReciprocateData reciprocateData;
	findPlayerData_by_TeamName(this->getManager().teamData.at(home).name, &reciprocateData);
	this->getManager().teamData.at(home) = convertFromDataSetToTeam(&reciprocateData);
	strcpy(this->getManager().teamData.at(home).name, manchesterUnited);

	// データ開放
	releaseReciprocateData(&reciprocateData);

	findPlayerData_by_TeamName(this->getManager().teamData.at(away).name, &reciprocateData);
	this->getManager().teamData.at(away) = convertFromDataSetToTeam(&reciprocateData);
	strcpy(this->getManager().teamData.at(away).name, chercy);
	out << "必要な２チームのチーム情報を取得完了" << endl;
	out << "home : " << manchesterUnited << ", away : " << chercy << endl;

	out << "チーム情報 : " << endl;
	out << "home : " << endl;
	out << this->getManager().teamData.at(home) << endl;
	out << "away : " << endl;
	out << this->getManager().teamData.at(away) << endl;

	this->getManager().setState(MANAGERSTATE_GAME);

	releaseReciprocateData(&reciprocateData);
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
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
 * @brief 状態が変更されたときに最初に実行される
 *---------------------------------------------------*/
void GameState::insertProcess()
{
	this->getManager().gameResult.clear();
}



/**----------------------------------------------------
 * @brief  メイン
 *---------------------------------------------------*/
void GameState::run()
{
	// 時間取得
	time_t gameStartTime;
	time(&gameStartTime);

	out << "Team " << this->getManager().teamData.at(home).name <<
		" and " << this->getManager().teamData.at(away).name << " is Game in Europe." << endl;

	int homeOffence = getTeamOffence(&this->getManager().teamData.at(home));
	int homeDefence = getTeamDefence(&this->getManager().teamData.at(home));
	int awayOffence = getTeamOffence(&this->getManager().teamData.at(away));
	int awayDefence = getTeamDefence(&this->getManager().teamData.at(away));

	// データの初期化
	for (int i = 0; i < homeAwayMax; ++i) {
		GameResult result;
		int offence = getTeamOffence(&this->getManager().teamData.at(i));
		out << i << ": " << endl;
		out << "TeamOffence : " << offence << endl;

		strcpy(result.name, this->getManager().teamData.at(home).name);
		result.time = gameStartTime;

		// ゴール数の計算
		if (offence > 2000) {
			result.score = 3;
		} else if (offence > 1800) {
			result.score = 2;
		} else {
			result.score = 1;
		}
		this->getManager().gameResult.push_back(result);
	}

	// 成績の診断
	if (this->getManager().gameResult.at(home).score == this->getManager().gameResult.at(away).score) {
		// 独自計算式。さほど意味はない。
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

	this->getManager().setState(MANAGERSTATE_RESULT);
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
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
 * @brief  メイン
 *---------------------------------------------------*/
void ResultState::run()
{
	//out << this->getManager().messageForNext << endl;
	out << this->getManager().teamData.at(home) << endl;
	out << this->getManager().teamData.at(away) << endl;

	sendGameResult(homeUserID, &this->getManager().gameResult.at(home));
	sendGameResult(awayUserID, &this->getManager().gameResult.at(away));

	this->getManager().setState(MANAGERSTATE_END);
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
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
 * @brief  メイン
 *---------------------------------------------------*/
void ReleaseState::run()
{
}


/**----------------------------------------------------
 * @brief   getter of StateName
 *              ベースクラスの関数のオーバーライド。
 * @return  状態の名前。
 *---------------------------------------------------*/
ManagerState ReleaseState::getState() const
{
	return MANAGERSTATE_END;
}



}    // namespace LeagueMode

