
#ifndef GAMEDATA_HPP_INCLUDED
#define GAMEDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <list>
#include <algorithm>
#include "Error.hpp"
#include "StreamObject.hpp"

/**
 * @brief ���[�U�Q�[���f�[�^
 * @author  Takuya Shishido
 * @date    2009.10.20 23:11:19
 * @version 0.01, Shishido Takuya, 2009.10.28 02:07
 */
struct UserData
{
private:

	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os      �X�g���[���I�u�W�F�N�g
	 * @param[in]  team    �o�̓I�u�W�F�N�g
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const UserData& userData)
	{
		os << userData.money << std::endl;
		os << userData.userID << std::endl;

		return os;
	}


public:


	//-----------------------------------------------------
	//  �C�e���[�^�̌^�錾
	//-----------------------------------------------------
	typedef std::list<int>                  HavingList;             //!< �_��ς݃`�[���̃R���e�i
	typedef std::list<int>                  AlliancableList;        //!< �_��\�ȃ`�[���̃R���e�i
	typedef std::list<int>::iterator        HavingListIte;          //!< �_��ς݃`�[���� ID �C�e���[�^
	typedef std::list<int>::iterator        AlliancableListIte;     //!< �_��\�ȃ`�[���� ID �C�e���[�^


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
	 * @brief     �������֐�
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
	 * @param[in]    teamID     �O�������`�[����ID
	 *---------------------------------------------------*/
	void unsetHavingTeamID(int teamID_) throw(Error::FindError);


	/**----------------------------------------------------
	 * @brief       �_��\�`�[���̐��̃Q�b�^
	 * @return      �_��\���`�[���̐�
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

	unsigned int        money;              //!< ������
	unsigned int        userID;             //!< ���[�U�ԍ�
	std::list<int>      havingTeamID;       //!< �_��ς݃`�[��ID
	std::list<int>      alliancableTeamID;  //!< �_��\�`�[��ID

};

#endif

