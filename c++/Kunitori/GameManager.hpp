
#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "AI.hpp"           // �`�[���̈ړ��Ȃǂ��Ǘ�
#include "Governor.hpp"     // �X�̊Ǘ����s���Ă��炤
#include "State.hpp"        // GameManager �̏�ԊǗ�
#include "GameData.hpp"     // �Q�[���f�[�^�ꌳ�Ǘ�
#include "Define.hpp"       // ��`���ꂽ�f�[�^�̕ۊǌ�


namespace NewMode {

/**
 * @brief �Q�[���Ǘ��N���X
 *          �Q�[���̊Ǘ����B�i�s�͂��Ȃ��B
 * @author  Takuya Shishido
 * @date    2009.10.20 23:11:19
 * @version 0.01, Shishido Takuya, 2009.10.20 23:11:19
 */
class GameManager
{
private:

	friend class State;
	friend class InitState;
	friend class OrdinaryState;
	friend class ShowAlliancableTeam;
	friend class SignWithTeam;
	friend class EndGame;

public:


	enum GameState
	{
		GAMESTATE_EXIT,     // �I��
		GAMESTATE_RUN,      // �p��
	};


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
	 *          ���C���̎d���́AcityContainer ��
	 *          action ���R���e�i�̍ŏ�����Ō�܂ŏ������邾��
	 * @return  GAMESTATE_EXIT => �Q�[���I��
	 * @return  GAMESTATE_RUN => �Q�[���p��
	 *---------------------------------------------------*/
	GameState run();







	/**----------------------------------------------------
	 * @brief        �h������ۂɂ��̊֐��o�R�Ŕh��
	 * @param[in]    cityID     �U�ߓ���X�̂h�c
	 *---------------------------------------------------*/
	void troopToCity(int myID, int placeID);




	/**----------------------------------------------------
	 * @brief   �X�̏������t�@�C���̖��O���擾
	 * @return  �X�̏������t�@�C���̖��O
	 *---------------------------------------------------*/
	std::string getCityConfigFileName() { return Define::cityConfigFileName; }



	/**----------------------------------------------------
	 * @brief   �`�[���̏������t�@�C���̖��O���擾
	 * @return  �`�[���̏������t�@�C���̖��O
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
	 * @brief   getter of State
	 * @return  ���݂̃X�e�[�g
	 *---------------------------------------------------*/
	State* getNowState() { return this->nowState; }


	/**----------------------------------------------------
	 * @brief   getter of State
	 * @return  �O��̃X�e�[�g
	 *---------------------------------------------------*/
	StateData getPreState() { return this->preStateID; }



private:

	AI                      ai;                 //!< �v�l�̑�̂��s��
	Governor                governor;           //!< �X�̐��������͑�̍s��


	// �X�e�[�g�����N���X�Q
	StateData               preStateID;         //!< �O��̃X�e�[�gID
	StateData               nowStateID;         //!< ���݂̃X�e�[�gID
	StateData               preRoopStateID;     //!< �O��̃��[�v�̃X�e�[�gID
	State*                  nowState;           //!< ���݂̃X�e�[�g
	std::vector<State*>     stateContainer;     //!< �X�e�[�g�Ǘ�

};    // class GameManager


}   // namespace NewMode

#endif

