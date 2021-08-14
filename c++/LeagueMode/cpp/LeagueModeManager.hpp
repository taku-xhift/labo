
#ifndef LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "LeagueModeManagerState.hpp"
#include "LeagueWork.hpp"
#include "TeamForCpp.hpp"
#include "GameResultForCpp.hpp"


namespace LeagueMode {

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
	static LeagueModeManager* getInstance()
	{
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
	static void destroyInstance()
	{
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
	ManagerState run();


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
	std::string getStateString(ManagerState state_) const;



	/**----------------------------------------------------
	 *  �����o
	 *----------------------------------------------------*/
	StateBase*                  nowState;           //!< ���݂̏�ԃI�u�W�F�N�g

	std::vector<StateBase*>     stateContainer;     //!< ��ԊǗ��R���e�i
	LeagueWork                  leagueWork;         //!< �Q�[���̃��C���̃f�[�^���Ǘ�����N���X
	ManagerState                preState;           //!< ���O�̃X�e�[�g�̖��O
	ManagerState                nextState;          //!< ���̃X�e�[�g�̖��O

	std::string                 messageForNext;     //!< ���̃X�e�[�g�ւ̃��b�Z�[�W��ۑ�

	std::vector<Team>           teamData;           //!< �ΐ킷��Q�`�[���̃`�[�����
	std::vector<GameResult>     gameResult;         //!< �������ʂ�ۑ�����
};    // class LeagueModeManager
}    // namespace LeagueMode

#endif

