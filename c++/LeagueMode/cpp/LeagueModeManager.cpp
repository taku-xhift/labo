/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "StreamObject.hpp"
#include "LeagueModeManager.hpp"
#include "MemoryLeakCheck.hpp"

//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int teamNum = 2;  //!< 対戦に関わるチーム数
}

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
	delete this->stateContainer.at(MANAGERSTATE_RELEASE);
	delete this->stateContainer.at(MANAGERSTATE_RESULT);
	delete this->stateContainer.at(MANAGERSTATE_GAME);
	delete this->stateContainer.at(MANAGERSTATE_GETDATA);
	delete this->stateContainer.at(MANAGERSTATE_TEAMSELECT);
	delete this->stateContainer.at(MANAGERSTATE_INIT);
	this->stateContainer.clear();
}

/**----------------------------------------------------
 * @brief   実行関数
 *              State Pattern で書かれているため、
 *              nowState に依存する処理が行われる。
 * @return  現在の状態の名前
 *----------------------------------------------------*/
ManagerState LeagueModeManager::run()
{
	// 出力
	this->opParameter();	// ゲーム全体の処理

	this->nowState->run();
	this->nowState->printout();     // 出力データ

	// 現在の状態の出力
	out << "Now State is " << this->getStateString(this->nowState->getState()) <<"!!!" << endl;

	// データ関連の更新
	this->leagueWork.update();

	return this->getNowState();
}



/**----------------------------------------------------
 * @brief  データ出力
 * @note    ボタンを押したときのみ
 *----------------------------------------------------*/
void LeagueModeManager::opParameter()
{
	out << "\n\n====================PrintStart====================" << endl;
//	out <<  __FILE__ << ", " << __FUNCTION__ << endl;
	out << "nowState => " << this->getStateString(this->getNowState()) << endl;
	out << "preState => " << this->getStateString(this->preState) << endl;
}



/**----------------------------------------------------
 * @brief constructor
 *           Singleton Pattern によっているため、private なコンストラクタ
 *----------------------------------------------------*/
LeagueModeManager::LeagueModeManager()
{
	this->stateContainer.resize(MANAGERSTATE_MAX);

	this->stateContainer.at(MANAGERSTATE_INIT) = new InitState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_TEAMSELECT) = new TeamSelectState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_GETDATA) = new GetDataState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_GAME) = new GameState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_RESULT) = new ResultState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_RELEASE) = new ReleaseState(*this, this->leagueWork);
	this->nowState = this->stateContainer.at(MANAGERSTATE_FIRST);

/*
	this->stateContainer.push_back(new InitState(*this, this->leagueWork));
	this->stateContainer.push_back(new TeamSelectState(*this, this->leagueWork));
	this->stateContainer.push_back(new GetDataState(*this, this->leagueWork));
	this->stateContainer.push_back(new GameState(*this, this->leagueWork));
	this->stateContainer.push_back(new ResultState(*this, this->leagueWork));
	this->stateContainer.push_back(new ReleaseState(*this, this->leagueWork));
	this->nowState = this->stateContainer.at(MANAGERSTATE_FIRST);
*/
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
	this->nowState = this->stateContainer.at(state_);
	this->nextState = nextState_;

	// 現在の導入処理を行う
	this->nowState->insertProcess();

//	out << __FILE__ << ", " << __FUNCTION__ << endl;
	out << "preState = " << this->getStateString(this->preState) << endl;
	out << "nowState = " << this->getStateString(this->nowState->getState()) << endl;
	out << "nextState = " << this->getStateString(this->nextState) << endl;
	out << "message = " << this->messageForNext << endl;
}



/**----------------------------------------------------
 * @brief 現在の状態を表示する
 *----------------------------------------------------*/
std::string LeagueModeManager::getStateString(ManagerState state_) const
{
	std::string state;

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
		case MANAGERSTATE_END:
			state = "End";
			break;
		default:
			state = "Invalid";
			break;
	}

	return state;
}



}    // namespace LeagueMode

