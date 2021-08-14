
#ifndef TEAM_HPP_INCLUDED
#define TEAM_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "StreamObject.hpp"



//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
class GameManager;


/**
 * @brief ��N���X�p�p�����[�^
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
	 * @param[in]    rhs    �f�[�^�������鑤
	 * @return       �ύX���������{��
	 *---------------------------------------------------*/
	TeamParameter& operator= (const TeamParameter& rhs);



	/**----------------------------------------------------
	 * @brief �������֐�
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os               �X�g���[���I�u�W�F�N�g
	 * @param[in]  cityParameter    �o�̓I�u�W�F�N�g
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


	int rhythm;     //!< ���q
	int stamina;    //!< �̗�

	int teamID;     //!< �`�[���h�c
	int warTimes;   //!< �퓬��
	int winTimes;   //!< ������
	int group;      //!< �����`�[��
	int restTime;   //!< �x�e����

	int homeTown;   //!< �������Ă���X�h�c
	int contract;   //!< �_���

	std::string name;   //!< �`�[����
};



/**
 * @brief ��N���X
 *          ��Ƃ��ĊǗ�����ŏ��N���X
 * @author  Takuya Shishido
 * @date    2009.10.20 22:58:12
 * @version 0.01, Shishido Takuya, 2009.10.20 22:58:12
 */
class Team
{
private:

	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os      �X�g���[���I�u�W�F�N�g
	 * @param[in]  team    �o�̓I�u�W�F�N�g
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
	 * @param[in]    rhs    �f�[�^�������鑤
	 * @return       �ύX���������{��
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
	 * @brief   �퓬�Ŏg�����߂� power �̃Q�b�^�B
	 *              ���q�Ȃǂ��������ꂽ���̂ƂȂ�
	 * @return  power of int type
	 *---------------------------------------------------*/
	int getTeamBattlePower() const {
		return this->power;
		//return TODO;
	}


	/**----------------------------------------------------
	 * @brief   �������̔�J���Z�֐�
	 *---------------------------------------------------*/
	void addTirednessInWin() {
		//TODO;
		this->tiredness += 10;
	}


	/**----------------------------------------------------
	 * @brief   �s�펞�̔�J���Z�֐�
	 *---------------------------------------------------*/
	void addTirednessInLose() {
		//TODO;
		this->tiredness += 20;
	}


private:

	GameManager& gameManager;    //!< GameManager

	TeamParameter teamParameter;    //!< Parameter
	int power;                      //!< ���
	int tiredness;                  //!< ��J�x

};    // class Team

#endif

