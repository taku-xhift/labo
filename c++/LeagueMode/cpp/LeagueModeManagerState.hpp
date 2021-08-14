
#ifndef LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "LeagueModeException.hpp"
#include "TeamForCpp.hpp"


//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
namespace LeagueMode {
	class LeagueModeManager;
	class LeagueWork;
}



namespace LeagueMode {

	/**
	 * @enum �Q�[���}�l�[�W���[�̃X�e�[�g�ꗗ
	 */
	enum ManagerState {
		MANAGERSTATE_FIRST,
		MANAGERSTATE_INIT = MANAGERSTATE_FIRST,
		MANAGERSTATE_TEAMSELECT,
		MANAGERSTATE_GETDATA,
		MANAGERSTATE_GAME,
		MANAGERSTATE_RESULT,
		MANAGERSTATE_RELEASE,
		MANAGERSTATE_END = MANAGERSTATE_RELEASE,
		MANAGERSTATE_MAX,
	};



/**
 * @brief  GameManager �̏�ԏ����N���X�B�x�[�X�N���X�B
 *          �p������邱�Ƃ�O��ɍ쐬���ꂽ�N���X�B
 * @author Takuya Shishido
 * @date 2009-10-17
 * @version 0.01
*/
class StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor.
	 * @param[in]   gameManager_    GameManager object.
	 * @param[in]   userWork_       Work object.
	 *---------------------------------------------------*/
	StateBase(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
		: leagueModeManager(leagueModeManager_)
		, leagueWork(leagueWork_)
	{
	}

	/**----------------------------------------------------
	 * @brief  destroctor
	 *          �p������邱�Ƃ�O��ɍ쐬����Ă��邽�߁A
	 *              virtual �ɂȂ��Ă���
	 *---------------------------------------------------*/
	virtual ~StateBase() {}

	/**----------------------------------------------------
	 * @brief  ���s�֐�
	 *          �e���e�ɂ���ĕς�镔���Ȃ̂� pure virtual
	 *---------------------------------------------------*/
	virtual void run() = 0;


	/**----------------------------------------------------
	 * @brief   �e�N���X�̖��O�̃Q�b�^�B
	 *              ���ꂪ GameManager �N���X�ɂƂ��Ă� getState() ��⍲�B
	 * @return  Child class's name.
	 *---------------------------------------------------*/
	virtual ManagerState getState() const = 0;


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
	 *---------------------------------------------------*/
	virtual void insertProcess() {}


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŌ�Ɏ��s�����
	 *---------------------------------------------------*/
	virtual void releaseProcess() {}


	/**----------------------------------------------------
	 * @brief ������ʂ�t�@�C���ɏo��
	 *---------------------------------------------------*/
	virtual void printout() {}



protected:

	/**----------------------------------------------------
	 * @brief �}�l�[�W���[�N���X�̃Q�b�^
	 * @note    ���ڂ̃A�N�Z�X�͋����ꂸ�A
	 *              �p���N���X��������o�R���ăA�N�Z�X����B
	 * @return  GameManager&    �Q�[���Ǘ��N���X
	 *---------------------------------------------------*/
	LeagueModeManager& getManager() { return this->leagueModeManager; }


	/**----------------------------------------------------
	 * @brief �}�l�[�W���[�N���X�̃Q�b�^
	 * @note    ���ڂ̃A�N�Z�X�͋����ꂸ�A
	 *              �p���N���X��������o�R���ăA�N�Z�X����B
	 * @return  GameManager&    �Q�[���Ǘ��N���X
	 *---------------------------------------------------*/
	LeagueWork& getWork() { return this->leagueWork; }


private:

	LeagueModeManager&  leagueModeManager;       //!< GameManager �{��
	LeagueWork&         leagueWork;          //!< ���[�U�[�p�f�[�^�{��
};


/**
 * @brief  �������̂��߂̃N���X
 *
 * @author  Takuya Shishido
 * @date    2010-04-02
 * @version 0.01
 */
class InitState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	InitState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~InitState()  {}


	/**----------------------------------------------------
	 * @brief  ���������s
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;
};



/**
 * @brief  �`�[���I���B�ŏ��͌Œ�l�Ńe�X�g���s���B
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class TeamSelectState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	TeamSelectState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~TeamSelectState()  {}


	/**----------------------------------------------------
	 * @brief  ���������s
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
	 *---------------------------------------------------*/
	void insertProcess();


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŌ�Ɏ��s�����
	 *---------------------------------------------------*/
	virtual void releaseProcess();



private:

	enum Step {
		STEP_FIRSTSTEP,
		STEP_SELECTFIESTTEAM = STEP_FIRSTSTEP,
		STEP_SELECTSECONDTEAM,
		STEP_LASTSTEP = STEP_SELECTSECONDTEAM,
		STEP_MAX,
	};


	/**----------------------------------------------------
	 * @brief �I�����ꂽ�ԍ������Ƀ`�[���̖��O����ꂽ
	 *          �`�[����Ԃ�
	 * @param[in]   selectedNumber_     �I�����ꂽ�ԍ�
	 * @return      ���������ɍ쐬���ꂽ Team
	 *---------------------------------------------------*/
	Team createTeamByName(int selectedNumber_) const throw(BadSelectException);


private:

	unsigned int            step;       //!< ������Ԃ�����
	std::vector<TeamList>   teamList;   //!< �ΐ킷��`�[���̔ԍ�
};


/**
 * @brief  �c�a ����f�[�^���擾����
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class GetDataState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	GetDataState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~GetDataState()  {}


	/**----------------------------------------------------
	 * @brief  ���C��
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
	 *---------------------------------------------------*/
	void insertProcess();


};



/**
 * @brief  ���������B���ʂ��܂Ƃ߂�܂ŁB
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class GameState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	GameState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~GameState()  {}


	/**----------------------------------------------------
	 * @brief  ���C��
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief ��Ԃ��ύX���ꂽ�Ƃ��ɍŏ��Ɏ��s�����
	 *---------------------------------------------------*/
	void insertProcess();


private:


	/**----------------------------------------------------
	 * @brief   �ΐ���s�����ۂɎ擾�ł���S�[�������v�Z
	 * @param[in]   offence_    �`�[���̑��U����
	 * @return  �S�[����
	 *---------------------------------------------------*/
	int getGoal(int offence_);
};



/**
 * @brief  �������ʂ�\������
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class ResultState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	ResultState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~ResultState()  {}


	/**----------------------------------------------------
	 * @brief  ���C��
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;
};



/**
 * @brief  �S�Ă̂܂Ƃ߂��s���B�J����K�v�ȏ����ȂǁB
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class ReleaseState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	ReleaseState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~ReleaseState()  {}


	/**----------------------------------------------------
	 * @brief  ���C��
	 *---------------------------------------------------*/
	void run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              �x�[�X�N���X�̊֐��̃I�[�o�[���C�h�B
	 * @return  ��Ԃ̖��O�B
	 *---------------------------------------------------*/
	ManagerState getState() const;
};




}    // namespace LeagueMode

#endif  // LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED

