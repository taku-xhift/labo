
#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "Define.hpp"



namespace NewMode {


enum StateData {
	STATEDATA_INVALID,                  //!< 無効なステート。主にチェック用。
	STATEDATA_INIT,                     //!< 初期化ステート
	STATEDATA_TURNSTART,                //!< ターンのはじめの処理を決めるステート
	STATEDATA_SHOWGROUPINFORMATION,     //!< グループ情報を表示する処理
	STATEDATA_SHOWTEAMINFORMATION,      //!< チーム情報を表示する処理
	STATEDATA_SHOWCITYINFORMATION,      //!< 街情報を表示する処理
	STATEDATA_SHOWALLIANCABLETEAM,      //!< 契約可能チームを表示する処理
	STATEDATA_SIGNWITHTEAM,             //!< チームと契約する処理
	STATEDATA_TROOP,                    //!< 派兵する処理
	STATEDATA_TURNFOLLOWINGUSER,        //!< 次のユーザにターンを回す処理
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
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class TurnStartState : public State
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
	TurnStartState(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~TurnStartState();


	/**----------------------------------------------------
	 * @brief   初期化メソッド
	 *---------------------------------------------------*/
	virtual void init();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


private:

	std::vector<StateData>    commandContainer;   //!< コマンドコンテナ

};    // class TurnStartState





/**
 * @brief グループ情報表示のメソッド
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class ShowGroupInformation : public State
{
private:

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	ShowGroupInformation(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~ShowGroupInformation();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class ShowGroupInformation





/**
 * @brief チーム情報を見せるためのメソッド
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class ShowTeamInformation : public State
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	ShowTeamInformation(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~ShowTeamInformation();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class ShowTeamInformation





/**
 * @brief 街情報を見せるためのメソッド
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class ShowCityInformation : public State
{

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	ShowCityInformation(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~ShowCityInformation();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class ShowCityInformation







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
 * @brief 作戦フェーズを終了して移動する
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 */
class TurnFollowingUser : public State
{

public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	TurnFollowingUser(GameManager& manager_, StateData stateData_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~TurnFollowingUser();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


};    // class TurnFollowingUser



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

#endif

