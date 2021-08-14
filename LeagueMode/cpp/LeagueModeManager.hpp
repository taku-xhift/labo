
#ifndef LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManagerState.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueWork.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/GameResultForCpp.hpp"


namespace LeagueMode {


	/**
	 * @brief ���[�O���[�h���ł��鏈���ꗗ�B
	 * @note    LeagueModeManager::executeModule �Ŏg�p����
	 */
	enum LeaugeModeManagerBehavior {
		LEAGUEMODEMANAGERBEHAVIOR_TEAMSELECT,   //!< �`�[���Z���N�g
		LEAGUEMODEMANAGERBEHAVIOR_AUTOGAME,     //!< ����Ȃ��Ŏ������ʂ��o��
		LEAGUEMODEMANAGERBEHAVIOR_MAX,
	};



/**
 * @brief ���[�O���Ǘ����邽�߂̃}�l�[�W���[
 *          
 * @author  Takuya Shishido
 * @date    2010.04.02 10:44:24
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 */
class LeagueModeManager
{
private:

	static LeagueModeManager* uniqueInstance;   //!< �V���O���g���Ȃ̂Ń��j�[�N�ȃI�u�W�F�N�g��`

	friend class InitState;
	friend class TeamSelectState;
	friend class GetDataState;
	friend class GameState;
	friend class ResultState;
	friend class ReleaseState;


public:

	/**----------------------------------------------------
	 * @brief �C���X�^���X�擾
	 *          �K�v�Ȏ��Ƀ��������m�ۂ�����̂ŁACreate �����Ȃ�����
	 * @return  GameManager �̃��j�[�N�ȃI�u�W�F�N�g
	 *----------------------------------------------------*/
	static LeagueModeManager* getInstance() {
		if (uniqueInstance == NULL) {
			uniqueInstance = new LeagueModeManager();
		}
		return uniqueInstance;
	}


	/**----------------------------------------------------
	 * @brief �C���X�^���X�̔j��
	 *          �C���X�^���X�̔j������邽�߂̃N���X�B
	 *          �m�ۂ��Ă��Ȃ������ꍇ�ł����S�B
	 *----------------------------------------------------*/
	static void destroyInstance() {
		if (uniqueInstance != NULL) {
			delete uniqueInstance;
			uniqueInstance = NULL;
		}
	}


	/**----------------------------------------------------
	 * @brief  destructor
	 *----------------------------------------------------*/
	~LeagueModeManager();


	/**----------------------------------------------------
	 * @brief   ���s�֐�
	 *              State Pattern �ŏ�����Ă��邽�߁A
	 *              nowState �Ɉˑ����鏈�����s����B
	 * @return  ���݂̏�Ԃ̖��O
	 *----------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief �����Ŋ��蓖�Ă�ꂽ�d���݂̂��s��
	 * @param[in]   state_          �������e�̎w��
	 *----------------------------------------------------*/
	static void executeModule(LeaugeModeManagerBehavior behavior_);


	/**----------------------------------------------------
	 * @brief  �f�[�^�o��
	 * @note    �{�^�����������Ƃ��̂�
	 *----------------------------------------------------*/
	void opParameter();


	/**----------------------------------------------------
	 * @breif ��Ԃ��Z�b�g����ۂɎ󂯕t���邽�߂̃Q�b�^
	 *----------------------------------------------------*/
	ManagerState getNowState() const { return this->nowState->getState(); }


	/**----------------------------------------------------
	 * @breif ��Ԃ𕶎���Ŏ擾����
	 *----------------------------------------------------*/
	const char* getNowStateByString() const { return this->getStateString(this->nowState->getState()); }


	/**----------------------------------------------------
	 * @brief   ���݂̏�Ԃ̖��O�擾
	 * @return  ���݂̏�Ԃ̖��O
	 *----------------------------------------------------*/
	ManagerState getPreState() const {
		return this->preState;
	}


	/**----------------------------------------------------
	 * @brief       ��Ԃ̃Z�b�^
	 * @param[in]   state_          ���̏�ԃN���X
	 * @param[in]   nextState_      state_ �̎��̎w��B�������K�����f�����Ƃ͌���Ȃ��B
	 *----------------------------------------------------*/
	void setState(ManagerState state_, ManagerState nextState_ = MANAGERSTATE_MAX);


private:

	/**----------------------------------------------------
	 * @brief constructor
	 *           Singleton Pattern �ɂ���Ă��邽�߁Aprivate �ȃR���X�g���N�^
	 *----------------------------------------------------*/
	LeagueModeManager();



	/**----------------------------------------------------
	 * @brief copy constructor
	 *          Singleton Pattern �ŋL�q����Ă��邽�߁A
	 *          �R�s�[�R���X�g���N�^�� private �Ŗ���`�ɂ���
	 *----------------------------------------------------*/
	LeagueModeManager(const LeagueModeManager& leagueModeManager_);



	/**----------------------------------------------------
	 * @brief operator =
	 *          Singleton Pattern �ŋL�q����Ă��邽�߁A
	 *          operator = �� private �Ŗ���`�ɂ���
	 *----------------------------------------------------*/
	LeagueModeManager& operator =(const LeagueModeManager& leagueModeManager_);



	/**----------------------------------------------------
	 * @brief ���݂̏�Ԃ𕶎���Ŏ擾����
	 *----------------------------------------------------*/
	const char* getStateString(ManagerState state_) const;



	/**----------------------------------------------------
	 * @brief state_ �Ŏw�肳�ꂽ�f�[�^���쐬����
	 * @param[in]   state_      �쐬���鏈��
	 *----------------------------------------------------*/
	StateBase* createState(ManagerState state_);


public:
	/**----------------------------------------------------
	 * @brief �`�[���Z���N�g�Ɋւ����A�̏������s��
	 *----------------------------------------------------*/
	void behaviorTeamSelect();



	/**----------------------------------------------------
	 * @brief �������ʌv�Z�Ɋւ����A�̏������s��
	 * @param[in]   homeTeam_   �z�[�����`�[���̖��O
	 * @param[in]   awayTeam_   �A�E�F�C���`�[���̖��O
	 *----------------------------------------------------*/
	static void behaviorGame(const char* homeTeam_, const char* awayTeam_);


private:
	/**----------------------------------------------------
	 *  �����o
	 *----------------------------------------------------*/
	StateBase*                  nowState;           //!< ���݂̏�ԃI�u�W�F�N�g

	//std::vector<StateBase*>     stateContainer;     //!< ��ԊǗ��R���e�i
	LeagueWork                  leagueWork;         //!< �Q�[���̃��C���̃f�[�^���Ǘ�����N���X
	ManagerState                preState;           //!< ���O�̃X�e�[�g�̖��O
	ManagerState                nextState;          //!< ���̃X�e�[�g�̖��O

	std::string                 messageForNext;     //!< ���̃X�e�[�g�ւ̃��b�Z�[�W��ۑ�

	std::vector<TeamData>       teamData;           //!< �ΐ킷��Q�`�[���̃`�[�����
	std::vector<GameResult>     gameResult;         //!< �������ʂ�ۑ�����

};    // class LeagueModeManager
}    // namespace LeagueMode

#endif

