/**
 * @file
 * @brief ゲームデータ管理モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.28 08:51:29
 *
 * @version 0.01, Shishido Takuya, 2009.10.28 08:51:29
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GAMEDATA_HPP_INCLUDED
#define GAMEDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <list>
#include <algorithm>
#include "Error.hpp"
#include "StreamObject.hpp"


namespace NewMode {



/**
 * @brief ユーザゲームデータ
 * @author  Takuya Shishido
 * @date    2009.10.20 23:11:19
 * @version 0.01, Shishido Takuya, 2009.10.28 02:07
 */
struct UserData
{
private:

	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os      ストリームオブジェクト
	 * @param[in]  team    出力オブジェクト
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const UserData& userData)
	{
		os << userData.money << std::endl;
		os << userData.userID << std::endl;

		return os;
	}


public:


	//-----------------------------------------------------
	//  イテレータの型宣言
	//-----------------------------------------------------
	typedef std::list<int>                  HavingList;             //!< 契約済みチームのコンテナ
	typedef std::list<int>                  AlliancableList;        //!< 契約可能なチームのコンテナ
	typedef std::list<int>::iterator        HavingListIte;          //!< 契約済みチームの ID イテレータ
	typedef std::list<int>::iterator        AlliancableListIte;     //!< 契約可能なチームの ID イテレータ


	/**----------------------------------------------------
	 * @brief     constructor
	 *---------------------------------------------------*/
	UserData()
		: money(0)
		, userID(0)
	{
	}

	/**----------------------------------------------------
	 * @brief     destructor
	 *---------------------------------------------------*/
	~UserData()
	{
	}


	/**----------------------------------------------------
	 * @brief     初期化関数
	 *---------------------------------------------------*/
	void init()
	{
		this->money = 0;
		this->userID = 0;
		this->havingTeamID.clear();
		this->alliancableTeamID.clear();
	}


	/**----------------------------------------------------
	 * @brief     getter of money
	 * @return    Reference of int type.
	 *---------------------------------------------------*/
	int getMoney() const {
		return this->money;
	}


	/**----------------------------------------------------
	 * @brief     getter of money
	 * @return    Reference of int type.
	 *---------------------------------------------------*/
	void addMoney(int money_) {
		this->money += money_;
	}


	/**----------------------------------------------------
	 * @brief        setter of money
	 * @param[in]    money_    A parameter to set.
	 *---------------------------------------------------*/
	void reduceMoney(int money_) {
		this->money -= money_;
	}



	/**----------------------------------------------------
	 * @brief     add havingTeam
	 * @return    Reference of int type.
	 *---------------------------------------------------*/
	void addHavingteam(int teamID_) {
		this->havingTeamID.push_back(teamID_);
	}


	/**----------------------------------------------------
	 * @brief        unset havingTeam
	 * @param[in]    teamID     外したいチームのID
	 *---------------------------------------------------*/
	void unsetHavingTeamID(int teamID_) throw(Error::FindError);


	/**----------------------------------------------------
	 * @brief       契約可能チームの数のゲッタ
	 * @return      契約可能名チームの数
	 *---------------------------------------------------*/
	std::list<int> getAlliancableTeam() const {
		return this->alliancableTeamID;
	}



	/**----------------------------------------------------
	 * @brief     getter of userID
	 * @return    Reference of unsigned int type.
	 *---------------------------------------------------*/
	unsigned int getUserID() const {
		return this->userID;
	}



private:

	unsigned int        money;              //!< 所持金
	unsigned int        userID;             //!< ユーザ番号
	std::list<int>      havingTeamID;       //!< 契約済みチームID
	std::list<int>      alliancableTeamID;  //!< 契約可能チームID

};


}   // namespace NewMode

#endif

