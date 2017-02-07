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
#include "City.hpp"         // 街の情報管理
#include "Team.hpp"         // チームの情報管理
#include "State.hpp"        // GameManager の状態管理
#include "GameData.hpp"     // ゲームデータ一元管理
#include "Define.hpp"       // 定義されたデータの保管庫



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
	friend class TurnStartState;
	friend class ShowGroupInformation;
	friend class ShowTeamInformation;
	friend class ShowCityInformation;
	friend class ShowAlliancableTeam;
	friend class SignWithTeam;
	friend class TurnFollowingUser;
	friend class EndGame;

public:


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
	 * @return  0 => ゲーム終了
	 * @return  1 => ゲーム継続
	 *---------------------------------------------------*/
	int run();







	/**----------------------------------------------------
	 * @brief        派兵する際にこの関数経由で派兵
	 * @param[in]    cityID     攻め入る街のＩＤ
	 *---------------------------------------------------*/
	void troopToCity(int myID, int placeID);



	/**----------------------------------------------------
	 * @brief      getter of teamParameter
	 * @param[in]  teamID_  チームのユニークナンバー
	 * @return     Reference of TeamParameter type.
	 *---------------------------------------------------*/
	const TeamParameter& getTeamParameter(int teamID_) const {
		return this->teamContainer.at(teamID_).getTeamParameter();
	}


	/**----------------------------------------------------
	 * @brief     getter of teamPower
	 * @return    Reference of int type.
	 *---------------------------------------------------*/
	int getTeamBasePower(int teamID_) const {
		return this->teamContainer.at(teamID_).getTeamBasePower();
	}


	/**----------------------------------------------------
	 * @brief     getter of teamPower
	 * @return    Reference of int type.
	 *---------------------------------------------------*/
	int getTeamBattlePower(int teamID_) const {
		return this->teamContainer.at(teamID_).getTeamBattlePower();
	}

	/**----------------------------------------------------
	 * @brief   battle with argumentID
	 * @retval  true    win having team
	 * @retval  false   lose having team
	 *---------------------------------------------------*/
	bool getWinner(int teamID, int troopID);


	/**----------------------------------------------------
	 * @brief     getter of cityParameter
	 * @return    Reference of CityParameter type.
	 *---------------------------------------------------*/
	const CityParameter& getCityparameter(int cityID) const;


	/**----------------------------------------------------
	 * @brief     getter of userData
	 * @return    Reference of UserData type.
	 *---------------------------------------------------*/
	const UserData& getUserData() const {
		return this->userData.at(this->presentUserID);
	}


	/**----------------------------------------------------
	 * @brief     getter of userData
	 * @param[in] 取得したいユーザの番号
	 * @return    Reference of UserData type.
	 *---------------------------------------------------*/
	const UserData& getUserData(int userID_) const {
		return this->userData.at(userID_);
	}


	/**----------------------------------------------------
	 * @brief     setter of userData
	 * @param[in]    userData    A parameter to set.
	 *---------------------------------------------------*/
	void setUserData(UserData& userData_) {
		this->userData.at(userData_.getUserID()) = userData_;
	}



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
	 * @brief set next userID to presentUserID
	 *---------------------------------------------------*/
	void setNextUser() {
		if (static_cast<unsigned int>(this->presentUserID) +1 > this->userData.size()) {
			this->presentUserID = 0;
		}
		else {
			++this->presentUserID;
		}
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

//	statric GameManager*    uniqueInstance;     //!< シングルトン用自オブジェクト
	int                     presentUserID;      //!< 現在ターンを向かえているユーザ
	std::vector<UserData>   userData;           //!< ユーザのゲームデータ

	std::vector<City>       cityContainer;      //!< 街保有コンテナ
	std::vector<Team>       teamContainer;      //!< チームコンテナ


	// ステート処理クラス群
	StateData               preStateID;         //!< 前回のステートID
	StateData               nowStateID;         //!< 現在のステートID
	StateData               preRoopStateID;     //!< 前回のループのステートID
	State*                  nowState;           //!< 現在のステート
	std::vector<State*>     stateContainer;     //!< ステート管理

};    // class GameManager

#endif

