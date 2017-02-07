/**
 * @file
 * @brief Team 単位で管理する駒
 *
 * @author Takuya Shishido
 * @date   2009.10.20 22:58:12
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 22:58:12
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef TEAM_HPP_INCLUDED
#define TEAM_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "StreamObject.hpp"
#include "Object.hpp"

namespace NewMode {

//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
class GameManager;


/**
 * @brief 駒クラス用パラメータ
 * @author  Takuya Shishido
 * @date    2009.10.20 22:58:12
 * @version 0.01, Shishido Takuya, 2009.10.20 22:58:12
 */
struct TeamParameter
{
public:
	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	TeamParameter();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~TeamParameter();



	/**----------------------------------------------------
	 * @brief      operator =
	 * @param[in]    rhs    データを代入する側
	 * @return       変更を加えた本体
	 *---------------------------------------------------*/
	TeamParameter& operator= (const TeamParameter& rhs);



	/**----------------------------------------------------
	 * @brief 初期化関数
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os               ストリームオブジェクト
	 * @param[in]  cityParameter    出力オブジェクト
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const TeamParameter& teamParameter)
	{
		os << "rhythm : " << teamParameter.rhythm << std::endl;
		os << "stamina : " << teamParameter.stamina << std::endl;
		os << "teamID : " << teamParameter.teamID << std::endl;
		os << "warTimes : " << teamParameter.warTimes << std::endl;
		os << "winTimes : " << teamParameter.winTimes << std::endl;
		os << "group : " << teamParameter.group << std::endl;
		os << "restTime : " << teamParameter.restTime << std::endl;
		os << "contract : " << teamParameter.contract << std::endl;
		os << "name : " << teamParameter.name << std::endl;

		return os;
	}


	int rhythm;     //!< 調子
	int stamina;    //!< 体力

	int teamID;     //!< チームＩＤ
	int warTimes;   //!< 戦闘回数
	int winTimes;   //!< 勝利回数
	int group;      //!< 所属チーム
	int restTime;   //!< 休憩時間

	int homeTown;   //!< 所属している街ＩＤ
	int contract;   //!< 契約金

	std::string name;   //!< チーム名
};



/**
 * @brief 駒クラス
 *          駒として管理する最小クラス
 * @author  Takuya Shishido
 * @date    2009.10.20 22:58:12
 * @version 0.01, Shishido Takuya, 2009.10.20 22:58:12
 */
class Team : public Object
{
private:

	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os      ストリームオブジェクト
	 * @param[in]  team    出力オブジェクト
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const Team& team)
	{
		os << team.getTeamParameter();
		os << team.power << std::endl;
		os << team.tiredness << std::endl;

		return os;
	}


public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	Team(GameManager& gameManager_, const TeamParameter& teamParameter_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~Team();


	/**----------------------------------------------------
	 * @brief      operator =
	 * @param[in]    rhs    データを代入する側
	 * @return       変更を加えた本体
	 *---------------------------------------------------*/
	Team& operator= (const Team& rhs);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief   battel with guardian
	 * @retval  true    win
	 * @retval  false   lose
	 *---------------------------------------------------*/
	bool battle(int battleTeamID);


	/**----------------------------------------------------
	 * @brief      setter of rhythm
	 * @param[in]  rhythm_    A parameter to set.
	 *---------------------------------------------------*/
	void setRhythm(int rhythm_) {
		this->teamParameter.rhythm = rhythm_;
	}



	/**----------------------------------------------------
	 * @brief   getter of teamParameter
	 * @return  Reference of TeamParameter type.
	 *---------------------------------------------------*/
	const TeamParameter& getTeamParameter() const {
		return this->teamParameter;
	}



	/**----------------------------------------------------
	 * @brief   getter of pawer
	 * @return  Reference of TeamParameter type.
	 *---------------------------------------------------*/
	int getTeamBasePower() const {
		return this->power;
	}


	/**----------------------------------------------------
	 * @brief   戦闘で使うための power のゲッタ。
	 *              調子なども加味されたものとなる
	 * @return  power of int type
	 *---------------------------------------------------*/
	int getTeamBattlePower() const {
		return this->power;
		//return TODO;
	}


	/**----------------------------------------------------
	 * @brief   勝利時の疲労加算関数
	 *---------------------------------------------------*/
	void addTirednessInWin() {
		//TODO;
		this->tiredness += 10;
	}


	/**----------------------------------------------------
	 * @brief   敗戦時の疲労加算関数
	 *---------------------------------------------------*/
	void addTirednessInLose() {
		//TODO;
		this->tiredness += 20;
	}


private:

	GameManager& gameManager;    //!< GameManager

	TeamParameter teamParameter;    //!< Parameter
	int power;                      //!< 戦力
	int tiredness;                  //!< 疲労度

};    // class Team


}   // namespace NewMode

#endif

