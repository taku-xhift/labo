/**
 * @file
 * @brief ゲーム管理モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.20 23:11:19
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 23:11:19
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "AI.hpp"           // チームの移動などを管理
#include "Governor.hpp"     // 街の管理を行ってもらう
#include "State.hpp"        // GameManager の状態管理
#include "GameData.hpp"     // ゲームデータ一元管理
#include "Define.hpp"       // 定義されたデータの保管庫


namespace NewMode {

/**
 * @brief ゲーム管理クラス
 *          ゲームの管理役。進行はしない。
 * @author  Takuya Shishido
 * @date    2009.10.20 23:11:19
 * @version 0.01, Shishido Takuya, 2009.10.20 23:11:19
 */
class GameManager
{
private:

	friend class State;
	friend class InitState;
	friend class OrdinaryState;
	friend class ShowAlliancableTeam;
	friend class SignWithTeam;
	friend class EndGame;

public:


	enum GameState
	{
		GAMESTATE_EXIT,     // 終了
		GAMESTATE_RUN,      // 継続
	};


	/**----------------------------------------------------
	 * @brief  destructor
	 *---------------------------------------------------*/
	~GameManager();


	/**----------------------------------------------------
	 * @brief  getter of Instance
	 *---------------------------------------------------*/
	static GameManager& getInstance() {
		static GameManager uniqueInstance;

		return uniqueInstance;
	}


	/**----------------------------------------------------
	 * @brief  main roop
	 *          メインの仕事は、cityContainer の
	 *          action をコンテナの最初から最後まで処理するだけ
	 * @return  GAMESTATE_EXIT => ゲーム終了
	 * @return  GAMESTATE_RUN => ゲーム継続
	 *---------------------------------------------------*/
	GameState run();







	/**----------------------------------------------------
	 * @brief        派兵する際にこの関数経由で派兵
	 * @param[in]    cityID     攻め入る街のＩＤ
	 *---------------------------------------------------*/
	void troopToCity(int myID, int placeID);




	/**----------------------------------------------------
	 * @brief   街の初期化ファイルの名前を取得
	 * @return  街の初期化ファイルの名前
	 *---------------------------------------------------*/
	std::string getCityConfigFileName() { return Define::cityConfigFileName; }



	/**----------------------------------------------------
	 * @brief   チームの初期化ファイルの名前を取得
	 * @return  チームの初期化ファイルの名前
	 *---------------------------------------------------*/
	std::string getTeamConfigFileName() { return Define::teamConfigFileName; }



private:


	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	GameManager();


	/**----------------------------------------------------
	 * @brief     initialize GameManager
	 *---------------------------------------------------*/
	void init(int playerNum);



	/**----------------------------------------------------
	 * @brief        setter of state
	 * @param[in]    state_    A parameter to set.
	 *---------------------------------------------------*/
	void setState(StateData stateData_) {
		this->preStateID = this->nowStateID;
		this->nowState = this->stateContainer.at(stateData_);
		this->nowStateID = this->nowState->getStateName();
	}




	/**----------------------------------------------------
	 * @brief   getter of State
	 * @return  現在のステート
	 *---------------------------------------------------*/
	State* getNowState() { return this->nowState; }


	/**----------------------------------------------------
	 * @brief   getter of State
	 * @return  前回のステート
	 *---------------------------------------------------*/
	StateData getPreState() { return this->preStateID; }



private:

	AI                      ai;                 //!< 思考の大体を行う
	Governor                governor;           //!< 街の政治活動は大体行う


	// ステート処理クラス群
	StateData               preStateID;         //!< 前回のステートID
	StateData               nowStateID;         //!< 現在のステートID
	StateData               preRoopStateID;     //!< 前回のループのステートID
	State*                  nowState;           //!< 現在のステート
	std::vector<State*>     stateContainer;     //!< ステート管理

};    // class GameManager


}   // namespace NewMode

#endif

