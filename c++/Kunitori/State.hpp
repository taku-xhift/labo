/**
 * @file
 * @brief GameManager の振る舞いを決める状態モジュール群
 *
 * @author Takuya Shishido
 * @date   2009.10.27 23:42:36
 *
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "Define.hpp"


#pragma warning (disable:4512)

namespace NewMode {


enum StateData {
	STATEDATA_INVALID,                  //!< 無効なステート。主にチェック用。
	STATEDATA_INIT,                     //!< 初期化ステート
	STATEDATA_ORDINARY,                 //!< 通常流れるステート
	STATEDATA_SHOWALLIANCABLETEAM,      //!< 契約可能チームを表示する処理
	STATEDATA_SIGNWITHTEAM,             //!< チームと契約する処理
	STATEDATA_ENDGAME,                  //!< ゲームの終了までの処理

	STATEDATA_NUM,                      //!< enum を管理するためのデータ
};

/**
 * @brief 継承されるベースクラス
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class State
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	State(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~State();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	virtual void action() = 0;


	/**----------------------------------------------------
	 * @brief   getter of stateName
	 * @return  stateName
	 *---------------------------------------------------*/
	StateData getStateName() const {
		return this->stateData;
	}


	/**----------------------------------------------------
	 * @brief   初期化用関数
	 *---------------------------------------------------*/
	virtual void init()  {}



protected:

	/**----------------------------------------------------
	 * @brief   GameManager へのアクセッサ
	 * @return  gameManager
	 *---------------------------------------------------*/
	GameManager& getManager() {
		return this->manager;
	}


private:

	GameManager& manager;       //!< GameManager 本体
	StateData    stateData;     //!< State を表すデータ

};    // class State




/**
 * @brief 初期化のためのステート
 * @author  Takuya Shishido
 * @date    2009/11/08 15:46
 * @version 0.01, Shishido Takuya, 2009/11/08 15:46
 */
class InitState : public State
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	InitState(GameManager& manager_, StateData stateData_)
		: State(manager_, stateData_)
	{
	}


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~InitState() {}


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


	/**----------------------------------------------------
	 * @brief   初期化メソッド
	 *---------------------------------------------------*/
	void init()  {}

};    // class INITState



/**
 * @brief ターンの始めの入力モジュール
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2010.01.29 19:03:40
 */
class OrdinaryState : public State
{
private:

	enum Command {
		COMMAND_INVALID,
		COMMAND_TROOP,
		COMMAND_SIGN_WITH_A_TEAM,
		COMMAND_GROUP_INFORMATION,
		COMMAND_CITY_INFORMATION,
		COMMAND_TEAM_INFORMATION,
		COMMAND_END_TURN,
		COMMAND_END_GAME,

		COMMAND_NUM,
	};

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	OrdinaryState(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~OrdinaryState();


	/**----------------------------------------------------
	 * @brief   初期化メソッド
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


private:

	std::vector<StateData>    commandContainer;   //!< コマンドコンテナ

};    // class TurnStartState




/**
 * @brief 契約可能なチームを表示するメソッド
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class ShowAlliancableTeam : public State
{

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	ShowAlliancableTeam(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~ShowAlliancableTeam();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class ShowAlliancableTeam



/**
 * @brief チームと契約するメソッド
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class SignWithTeam : public State
{

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	SignWithTeam(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~SignWithTeam();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class SignWithTeam




/**
 * @brief ゲームの終了を管理
 * @author  Takuya Shishido
 * @date    2009.11.01 18:45
 * @version 0.01, Shishido Takuya, 2009.11.01 18:45
 */
class EndGame : public State
{

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	EndGame(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~EndGame();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class EndGame


}   // namespace NewMode

#pragma warning (default: 4512)

#endif

