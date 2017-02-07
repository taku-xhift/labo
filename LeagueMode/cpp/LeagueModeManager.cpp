/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManager.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/StreamObject.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int teamNum = 2;  //!< 対戦に関わるチーム数
}


//-----------------------------------------------------
//  function
//-----------------------------------------------------
namespace LeagueMode {

/**
 * @brief 処理を一括して請け負うファンクタ。
 * @note    LeagueModeManager::run の戻り値が RUNSTATE_FINISH になるまで
 *              ループが回り続けるので注意
 *
 * @author Takuya Shishido
 * @date   2010-04-27
 * @version 0.01
*/
struct Functor_Execute
{

	/**----------------------------------------------------
	 * @brief constructor
	 * @param[in]   manager_    LeagueModeManager 本体。run が呼び出される
	 *---------------------------------------------------*/
	explicit Functor_Execute(LeagueModeManager& manager_) : manager(manager_) {}



	/**----------------------------------------------------
	 * @brief ファンクタ本体
	 * @note    クラス本体の説明をよく読むこと
	 * @param[in]   state_      処理内容の選択
	 *---------------------------------------------------*/
	void operator()(ManagerState state_) {
		this->manager.setState(state_);
		while (this->manager.run() != RUNSTATE_FINISH) {
		}
	}

private:

	LeagueModeManager& manager;     //!< リーグモード管理オブジェクト
};

}    // namespace LeagueMode


//-----------------------------------------------------
//  using
//-----------------------------------------------------
using namespace so;


//--------------------------------------------------------------
//  declaration
//--------------------------------------------------------------
LeagueMode::LeagueModeManager* LeagueMode::LeagueModeManager::uniqueInstance = (LeagueMode::LeagueModeManager*)NULL;



namespace LeagueMode {

/**----------------------------------------------------
 * @brief  destructor
 *----------------------------------------------------*/
LeagueModeManager::~LeagueModeManager()
{
	safeDelete(this->nowState);
}


/**----------------------------------------------------
 * @brief   実行関数
 *              State Pattern で書かれているため、
 *              nowState に依存する処理が行われる。
 * @return  現在の状態の名前
 *----------------------------------------------------*/
RunState LeagueModeManager::run()
{
	// 出力
	this->opParameter();	// ゲーム全体の処理

	RunState result = this->nowState->run();
	this->nowState->printout();     // 出力データ

	// 現在の状態の出力
	out << "Now State is " << this->getStateString(this->nowState->getState()) <<"!!!" << endl;

	// データ関連の更新
	this->leagueWork.update();

	return result;
}


/**----------------------------------------------------
 * @brief 引数で割り当てられた仕事のみを行う
 * @param[in]   state_          処理内容の指定
 *----------------------------------------------------*/
void LeagueModeManager::executeModule(LeaugeModeManagerBehavior behavior_)
{
	//TODO
	switch (behavior_) {
	    case LEAGUEMODEMANAGERBEHAVIOR_TEAMSELECT: {
			LeagueMode::LeagueModeManager::getInstance()->behaviorTeamSelect();
			break;
		}
	    case LEAGUEMODEMANAGERBEHAVIOR_AUTOGAME: {
			// TODO
			//LeagueMode::LeagueModeManager::getInstance()->behaviorGame();
			break;
		}
		case LEAGUEMODEMANAGERBEHAVIOR_MAX:
		// ↓ through down
		default: {
			assert(0);
		}
	}
}


/**----------------------------------------------------
 * @brief  データ出力
 * @note    ボタンを押したときのみ
 *----------------------------------------------------*/
void LeagueModeManager::opParameter()
{
	out << "\n\n====================PrintStart====================" << endl;
	out << "nowState => " << this->getStateString(this->getNowState()) << endl;
	out << "preState => " << this->getStateString(this->preState) << endl;
}



/**----------------------------------------------------
 * @brief constructor
 *           Singleton Pattern によっているため、private なコンストラクタ
 *----------------------------------------------------*/
LeagueModeManager::LeagueModeManager() : nowState(NULL)
{
	this->preState = MANAGERSTATE_FIRST;
	this->nowState = this->createState(MANAGERSTATE_FIRST);
	this->nextState = MANAGERSTATE_MAX;
}


/**----------------------------------------------------
 * @brief       状態のセッタ
 * @param[in]   state_  次の状態クラス
 *----------------------------------------------------*/
void LeagueModeManager::setState(ManagerState state_, ManagerState nextState_ /*= MANAGERSTATE_MAX*/)
{
	// まずは前のステートの終了処理を行う
	this->nowState->releaseProcess();

	// 状態の移行をして
	this->preState = this->nowState->getState();
	safeDelete(this->nowState);
	this->nowState = this->createState(state_);
	this->nextState = nextState_;

	// 現在の導入処理を行う
	this->nowState->insertProcess();

	out << "preState = " << this->getStateString(this->preState) << endl;
	out << "nowState = " << this->getStateString(this->nowState->getState()) << endl;
	out << "nextState = " << this->getStateString(this->nextState) << endl;
	out << "message = " << this->messageForNext << endl;
}


/**----------------------------------------------------
 * @brief 現在の状態を文字列で取得する
 * @return  状態の文字列の先頭ポインタ
 *----------------------------------------------------*/
const char* LeagueModeManager::getStateString(ManagerState state_) const
{
	const char* state;

	switch (state_) {
		case MANAGERSTATE_INIT:
			state = "init";
			break;
		case MANAGERSTATE_TEAMSELECT:
			state = "TeamSelect";
			break;
		case MANAGERSTATE_GETDATA:
			state = "GetData";
			break;
		case MANAGERSTATE_GAME:
			state = "Game";
			break;
		case MANAGERSTATE_RESULT:
			state = "Result";
			break;
		case MANAGERSTATE_RELEASE:
			state = "Release";
			break;
		case MANAGERSTATE_END:
			state = gameEnd;
			break;
		default:
			state = "Invalid";
			break;
	}

	return state;
}


/**----------------------------------------------------
 * @brief state_ で指定されたデータを作成する
 * @param[in]   state_      作成する処理
 *----------------------------------------------------*/
StateBase* LeagueModeManager::createState(ManagerState state_)
{
	switch (state_) {
        case MANAGERSTATE_INIT: {
			return New InitState(*this, this->leagueWork);
		}
		case MANAGERSTATE_TEAMSELECT: {
			return New TeamSelectState(*this, this->leagueWork);
		}
        case MANAGERSTATE_GETDATA: {
			return New GetDataState(*this, this->leagueWork);
		}
        case MANAGERSTATE_GAME: {
			return New GameState(*this, this->leagueWork);
		}
        case MANAGERSTATE_RESULT: {
			return New ResultState(*this, this->leagueWork);
		}
        case MANAGERSTATE_RELEASE: {
			return New ReleaseState(*this, this->leagueWork);
		}
        case MANAGERSTATE_MAX:
		// ↓ through down
		default: {
			assert(0);
			return NULL;
		}
	}
}



/**----------------------------------------------------
 * @brief チームセレクトに関する一連の処理を行う
 *----------------------------------------------------*/
void LeagueModeManager::behaviorTeamSelect()
{
	std::vector<ManagerState> list;
	list.push_back(MANAGERSTATE_INIT);
	list.push_back(MANAGERSTATE_TEAMSELECT);
	list.push_back(MANAGERSTATE_RELEASE);

	std::for_each(list.begin(), list.end(), Functor_Execute(*this));
}



/**----------------------------------------------------
 * @brief 試合結果計算に関する一連の処理を行う
 *----------------------------------------------------*/
void LeagueModeManager::behaviorGame(const char* homeTeam_, const char* awayTeam_)
{
	getInstance()->teamData.resize(2);
	strcpy(getInstance()->teamData.at(home).name, homeTeam_);
	strcpy(getInstance()->teamData.at(away).name, awayTeam_);

	std::vector<ManagerState> list;
	list.push_back(MANAGERSTATE_INIT);
	list.push_back(MANAGERSTATE_GETDATA);
	list.push_back(MANAGERSTATE_GAME);
	list.push_back(MANAGERSTATE_RESULT);
	list.push_back(MANAGERSTATE_RELEASE);

	std::for_each(list.begin(), list.end(), Functor_Execute(*getInstance()));
}




}    // namespace LeagueMode

