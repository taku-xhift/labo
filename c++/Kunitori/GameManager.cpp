
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <algorithm>
#include "StreamObject.hpp"
#include "GameManager.hpp"
#include "Define.hpp"


using namespace so;


namespace NewMode {


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
	case STATEDATA_ORDINARY:
		return new OrdinaryState(manager_, stateData_);
	case STATEDATA_SHOWALLIANCABLETEAM:
		return new ShowAlliancableTeam(manager_, stateData_);
	case STATEDATA_SIGNWITHTEAM:
		return new SignWithTeam(manager_, stateData_);
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
	: preStateID(STATEDATA_INVALID)
	, nowStateID(STATEDATA_INVALID)
{
	// State ���쐬
	makeStates(*this, this->stateContainer);

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
	// ���̑��̃p�����[�^
	this->preStateID = STATEDATA_INIT;
	this->nowStateID = STATEDATA_ORDINARY;

	this->nowState = stateContainer.at(STATEDATA_ORDINARY);
}


/**----------------------------------------------------
 * @brief main roop
 *---------------------------------------------------*/
GameManager::GameState GameManager::run()
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
		return GAMESTATE_EXIT;
	} else {
		return GAMESTATE_RUN;
	}
}


}   // namespace NewMode

