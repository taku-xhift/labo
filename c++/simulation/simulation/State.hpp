
#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "Define.hpp"



namespace NewMode {


enum StateData {
	STATEDATA_INVALID,                  //!< �����ȃX�e�[�g�B��Ƀ`�F�b�N�p�B
	STATEDATA_INIT,                     //!< �������X�e�[�g
	STATEDATA_TURNSTART,                //!< �^�[���̂͂��߂̏��������߂�X�e�[�g
	STATEDATA_SHOWGROUPINFORMATION,     //!< �O���[�v����\�����鏈��
	STATEDATA_SHOWTEAMINFORMATION,      //!< �`�[������\�����鏈��
	STATEDATA_SHOWCITYINFORMATION,      //!< �X����\�����鏈��
	STATEDATA_SHOWALLIANCABLETEAM,      //!< �_��\�`�[����\�����鏈��
	STATEDATA_SIGNWITHTEAM,             //!< �`�[���ƌ_�񂷂鏈��
	STATEDATA_TROOP,                    //!< �h�����鏈��
	STATEDATA_TURNFOLLOWINGUSER,        //!< ���̃��[�U�Ƀ^�[�����񂷏���
	STATEDATA_ENDGAME,                  //!< �Q�[���̏I���܂ł̏���

	STATEDATA_NUM,                      //!< enum ���Ǘ����邽�߂̃f�[�^
};

/**
 * @brief �p�������x�[�X�N���X
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
	 * @brief   �������p�֐�
	 *---------------------------------------------------*/
	virtual void init()  {}



protected:

	/**----------------------------------------------------
	 * @brief   GameManager �ւ̃A�N�Z�b�T
	 * @return  gameManager
	 *---------------------------------------------------*/
	GameManager& getManager() {
		return this->manager;
	}


private:

	GameManager& manager;       //!< GameManager �{��
	StateData    stateData;     //!< State ��\���f�[�^

};    // class State




/**
 * @brief �������̂��߂̃X�e�[�g
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
	 * @brief   ���������\�b�h
	 *---------------------------------------------------*/
	void init()  {}

};    // class INITState



/**
 * @brief �^�[���̎n�߂̓��̓��W���[��
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
	 * @brief   ���������\�b�h
	 *---------------------------------------------------*/
	virtual void init();


	/**----------------------------------------------------
	 * @brief execute function
	 *---------------------------------------------------*/
	void action();


private:

	std::vector<StateData>    commandContainer;   //!< �R�}���h�R���e�i

};    // class TurnStartState





/**
 * @brief �O���[�v���\���̃��\�b�h
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
 * @brief �`�[�����������邽�߂̃��\�b�h
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
 * @brief �X���������邽�߂̃��\�b�h
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
 * @brief �_��\�ȃ`�[����\�����郁�\�b�h
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
 * @brief �`�[���ƌ_�񂷂郁�\�b�h
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
 * @brief ���t�F�[�Y���I�����Ĉړ�����
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
 * @brief �Q�[���̏I�����Ǘ�
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

