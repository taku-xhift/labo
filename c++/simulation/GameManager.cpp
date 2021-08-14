
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <algorithm>
#include "StreamObject.hpp"
#include "GameManager.hpp"
#include "Define.hpp"


using namespace so;

//-----------------------------------------------------
//  functor
//-----------------------------------------------------
/**
 * @brief �������p�̃t�@���N�^
 * @author  Takuya Shishido
 * @date    2009/11/03 22:44
 * @version 0.01, Shishido Takuya, 2009/11/03 22:44
 */
template<typename Type>
class Initializer
{
public:

	/**----------------------------------------------------
	 * @brief operator()
	 * @note    ����������Ɉ����t�@���N�^�B
	 *          �g�����͂ǂ����������Ă݂����������B
	 * @param[in]   data    �������������f�[�^
	 *---------------------------------------------------*/
	void operator() (Type& data) {
		data.init();
	}
};

/**
 * @brief �f�[�^�� delete ����ɐ�������
 * @author  Takuya Shishido
 * @date    2009/11/04 0:08
 * @version 0.01, Shishido Takuya, 2009/11/04 0:08
 */
template<typename Type>
class Deleter
{
public:

	/**----------------------------------------------------
	 * @brief operator()
	 * @note    delete ����Ɉ����t�@���N�^�B
	 * @param[in]   data    �����������f�[�^
	 *---------------------------------------------------*/
	void operator() (const Type& data) {
		delete data;
	}
};


/**----------------------------------------------------
 * @brief �����ɂ��킹�� State* �����o��
 * @param[in]   manager_     �Q�[���}�l�[�W���[
 * @param[in]   stateData_   �~���� State �̎w��
 * @return  �R���X�g���N�^�ɂ���č����f�[�^�̃A�h���X
 *---------------------------------------------------*/
State* makeState(GameManager& manager_, StateData stateData_)
{
	// �n���ꂽ�f�[�^�̗L�������`�F�b�N
	if (stateData_ > STATEDATA_NUM) {
		out << __FILE__ << __LINE__ << "���g�̏�Ԃ��󂯎��܂����̂ŁA�������܂�" << endl;
		return NULL;
	}


	// ��L�֖���N���A�������̂̂݃`�F�b�N���ăf�[�^�쐬
	switch (stateData_) {
	case STATEDATA_INVALID:
		return NULL;
	case STATEDATA_INIT:
		return new InitState(manager_, stateData_);
	case STATEDATA_TURNSTART:
		return new TurnStartState(manager_, stateData_);
	case STATEDATA_SHOWGROUPINFORMATION:
		return new ShowGroupInformation(manager_, stateData_);
	case STATEDATA_SHOWTEAMINFORMATION:
		return new ShowTeamInformation(manager_, stateData_);
	case STATEDATA_SHOWCITYINFORMATION:
		return new ShowCityInformation(manager_, stateData_);
	case STATEDATA_SHOWALLIANCABLETEAM:
		return new ShowAlliancableTeam(manager_, stateData_);
	case STATEDATA_SIGNWITHTEAM:
		return new SignWithTeam(manager_, stateData_);
	case STATEDATA_TURNFOLLOWINGUSER:
		return new TurnFollowingUser(manager_, stateData_);
	case STATEDATA_ENDGAME:
		return new EndGame(manager_, stateData_);
	default:
		out << "�����ȃf�[�^���n����܂���" << endl;
		return NULL;
	}
}


/**----------------------------------------------------
 * @brief �����ɂ�������R���e�i��
 *          StateData �̐������� State* ������ē����B
 *          State �̒��g�� StateData �Ɍ����������g
 * @param[in]   manager     GameManager �f�[�^�B
 * @param[in]   container   push_back �̎g������́B
  *---------------------------------------------------*/
template<typename Type>
void makeStates(GameManager& manager, Type& container)
{
	State* state;

	// �����I�� State �̐����� State ������ĕۑ�
	for (unsigned int i = 0; i < STATEDATA_NUM; ++i) {
		state = makeState(manager, static_cast<StateData>(i));
		container.push_back(state);
		//delete state;
	}
}


/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
GameManager::GameManager()
	: presentUserID(0)
	, preStateID(STATEDATA_INVALID)
	, nowStateID(STATEDATA_INVALID)
{
	// State ���쐬
	makeStates(*this, this->stateContainer);

	// �X�̃f�[�^�쐬
	CityParameter cityParameter;
	for (int i = 0; i < 10; ++i) {
		City city(*this, cityParameter);
		this->cityContainer.push_back(city);
	}

	// �`�[���̃f�[�^�쐬
	TeamParameter teamParameter;
	for (int i = 0; i < 10; ++i) {
		Team team(*this, teamParameter);
		this->teamContainer.push_back(team);
	}

	// �������X�e�[�g
	//this->init();

	// �X�e�[�g�̌���
	this->nowState = this->stateContainer.at(STATEDATA_INIT);
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
GameManager::~GameManager()
{
	// ��ԊǗ��N���X�̃R���e�i������
	this->stateContainer.clear();
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
void GameManager::init(int playerNum)
{
	// ���[�U�f�[�^�̏�����
	this->userData.resize(playerNum);
	std::for_each(this->userData.begin(), this->userData.end(), Initializer<UserData>());

	// �X�̏���������
	std::for_each(this->cityContainer.begin(), this->cityContainer.end(), Initializer<City>());

	// �`�[���̏���������
	std::for_each(this->teamContainer.begin(), this->teamContainer.end(), Initializer<Team>());

	// ���̑��̃p�����[�^
	this->preStateID = STATEDATA_INIT;
	this->nowStateID = STATEDATA_TURNSTART;

	this->nowState = stateContainer.at(STATEDATA_TURNSTART);
}


/**----------------------------------------------------
 * @brief main roop
 *---------------------------------------------------*/
int GameManager::run()
{
	// �w�肳�ꂽ��Ԃ̎��s�֐����Ăяo��
	this->nowState->action();


	// �O��̃��[�v�ł̃X�e�[�g�̕ۑ�
	// �X�e�[�g�̕ω����N���Ă���Ήߋ��̂��̂�ۑ�
	if (this->preRoopStateID != this->preStateID) {
		this->preRoopStateID = this->preStateID;
	// �X�e�[�g�̕ω����N���Ă��Ȃ���Ό��݂̃X�e�[�g��ۑ�
	} else {
		this->preRoopStateID = this->nowStateID;
	}

	// �I�������𖞂������H
	if (this->nowState->getStateName() == STATEDATA_ENDGAME) {
		return 0;
	} else {
		return 1;
	}
}


/**----------------------------------------------------
 * @brief        �h������ۂɂ��̊֐��o�R�Ŕh��
 * @param[in]    cityID     �U�ߓ���X�̂h�c
 *---------------------------------------------------*/
void GameManager::troopToCity(int myID, int placeID)
{
	this->cityContainer.at(placeID).addTroopersID(this->cityContainer.at(myID).getTroopersID());
	
}


/**----------------------------------------------------
 * @brief   battle with argumentID
 * @retval  true    win having team
 * @retval  false   lose having team
 *---------------------------------------------------*/
bool GameManager::getWinner(int teamID, int troopID)
{
	bool result = true;

	Team team = this->teamContainer.at(teamID);
	result = team.battle(troopID);

	if (result == true) {
		// �����҂ɏ������̔�J
		this->teamContainer.at(teamID).addTirednessInWin();
		// �s�k�҂ɔs�k���̔�J
		this->teamContainer.at(troopID).addTirednessInLose();
	} else {
		// �����҂ɏ������̔�J
		this->teamContainer.at(troopID).addTirednessInWin();
		// �s�k�҂ɔs�k���̔�J
		this->teamContainer.at(teamID).addTirednessInLose();
	}

	// ���ʂ̕ԓ�
	return result;
}


/**----------------------------------------------------
 * @brief     getter of cityParameter
 * @return    Reference of CityParameter type.
 *---------------------------------------------------*/
const CityParameter& GameManager::getCityparameter(int cityID) const
{
	try {
		return this->cityContainer.at(cityID).getCityParameter();
	} catch (...) {
		out << "�L���� ID ���w�肵�Ă�������" << endl;
	}
}



