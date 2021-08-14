
#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "City.hpp"         // �X�̏��Ǘ�
#include "Team.hpp"         // �`�[���̏��Ǘ�
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
	 *          ���C���̎d���́AcityContainer ��
	 *          action ���R���e�i�̍ŏ�����Ō�܂ŏ������邾��
	 * @return  0 => �Q�[���I��
	 * @return  1 => �Q�[���p��
	 *---------------------------------------------------*/
	int run();







	/**----------------------------------------------------
	 * @brief        �h������ۂɂ��̊֐��o�R�Ŕh��
	 * @param[in]    cityID     �U�ߓ���X�̂h�c
	 *---------------------------------------------------*/
	void troopToCity(int myID, int placeID);



	/**----------------------------------------------------
	 * @brief      getter of teamParameter
	 * @param[in]  teamID_  �`�[���̃��j�[�N�i���o�[
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
	 * @param[in] �擾���������[�U�̔ԍ�
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
	 * @return  ���݂̃X�e�[�g
	 *---------------------------------------------------*/
	State* getNowState() { return this->nowState; }


	/**----------------------------------------------------
	 * @brief   getter of State
	 * @return  �O��̃X�e�[�g
	 *---------------------------------------------------*/
	StateData getPreState() { return this->preStateID; }



private:

//	statric GameManager*    uniqueInstance;     //!< �V���O���g���p���I�u�W�F�N�g
	int                     presentUserID;      //!< ���݃^�[�����������Ă��郆�[�U
	std::vector<UserData>   userData;           //!< ���[�U�̃Q�[���f�[�^

	std::vector<City>       cityContainer;      //!< �X�ۗL�R���e�i
	std::vector<Team>       teamContainer;      //!< �`�[���R���e�i


	// �X�e�[�g�����N���X�Q
	StateData               preStateID;         //!< �O��̃X�e�[�gID
	StateData               nowStateID;         //!< ���݂̃X�e�[�gID
	StateData               preRoopStateID;     //!< �O��̃��[�v�̃X�e�[�gID
	State*                  nowState;           //!< ���݂̃X�e�[�g
	std::vector<State*>     stateContainer;     //!< �X�e�[�g�Ǘ�

};    // class GameManager


}   // namespace NewMode

#endif

