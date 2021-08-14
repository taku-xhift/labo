
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "StreamObject.hpp"
#include "LeagueModeManager.hpp"
#include "MemoryLeakCheck.hpp"

//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int teamNum = 2;  //!< �ΐ�Ɋւ��`�[����
}

//-----------------------------------------------------
//  using
//-----------------------------------------------------
using namespace so;


//--------------------------------------------------------------
//  declaration
//--------------------------------------------------------------
LeagueMode::LeagueModeManager* LeagueMode::LeagueModeManager::uniqueInstance = (LeagueMode::LeagueModeManager*)NULL;



namespace LeagueMode {

/**----------------------------------------------------
 * @brief  destructor
 *----------------------------------------------------*/
LeagueModeManager::~LeagueModeManager()
{
	delete this->stateContainer.at(MANAGERSTATE_RELEASE);
	delete this->stateContainer.at(MANAGERSTATE_RESULT);
	delete this->stateContainer.at(MANAGERSTATE_GAME);
	delete this->stateContainer.at(MANAGERSTATE_GETDATA);
	delete this->stateContainer.at(MANAGERSTATE_TEAMSELECT);
	delete this->stateContainer.at(MANAGERSTATE_INIT);
	this->stateContainer.clear();
}

/**----------------------------------------------------
 * @brief   ���s�֐�
 *              State Pattern �ŏ�����Ă��邽�߁A
 *              nowState �Ɉˑ����鏈�����s����B
 * @return  ���݂̏�Ԃ̖��O
 *----------------------------------------------------*/
ManagerState LeagueModeManager::run()
{
	// �o��
	this->opParameter();	// �Q�[���S�̂̏���

	this->nowState->run();
	this->nowState->printout();     // �o�̓f�[�^

	// ���݂̏�Ԃ̏o��
	out << "Now State is " << this->getStateString(this->nowState->getState()) <<"!!!" << endl;

	// �f�[�^�֘A�̍X�V
	this->leagueWork.update();

	return this->getNowState();
}



/**----------------------------------------------------
 * @brief  �f�[�^�o��
 * @note    �{�^�����������Ƃ��̂�
 *----------------------------------------------------*/
void LeagueModeManager::opParameter()
{
	out << "\n\n====================PrintStart====================" << endl;
//	out <<  __FILE__ << ", " << __FUNCTION__ << endl;
	out << "nowState => " << this->getStateString(this->getNowState()) << endl;
	out << "preState => " << this->getStateString(this->preState) << endl;
}



/**----------------------------------------------------
 * @brief constructor
 *           Singleton Pattern �ɂ���Ă��邽�߁Aprivate �ȃR���X�g���N�^
 *----------------------------------------------------*/
LeagueModeManager::LeagueModeManager()
{
	this->stateContainer.resize(MANAGERSTATE_MAX);

	this->stateContainer.at(MANAGERSTATE_INIT) = new InitState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_TEAMSELECT) = new TeamSelectState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_GETDATA) = new GetDataState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_GAME) = new GameState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_RESULT) = new ResultState(*this, this->leagueWork);
	this->stateContainer.at(MANAGERSTATE_RELEASE) = new ReleaseState(*this, this->leagueWork);
	this->nowState = this->stateContainer.at(MANAGERSTATE_FIRST);

/*
	this->stateContainer.push_back(new InitState(*this, this->leagueWork));
	this->stateContainer.push_back(new TeamSelectState(*this, this->leagueWork));
	this->stateContainer.push_back(new GetDataState(*this, this->leagueWork));
	this->stateContainer.push_back(new GameState(*this, this->leagueWork));
	this->stateContainer.push_back(new ResultState(*this, this->leagueWork));
	this->stateContainer.push_back(new ReleaseState(*this, this->leagueWork));
	this->nowState = this->stateContainer.at(MANAGERSTATE_FIRST);
*/
}


/**----------------------------------------------------
 * @brief       ��Ԃ̃Z�b�^
 * @param[in]   state_  ���̏�ԃN���X
 *----------------------------------------------------*/
void LeagueModeManager::setState(ManagerState state_, ManagerState nextState_ /*= MANAGERSTATE_MAX*/)
{
	// �܂��͑O�̃X�e�[�g�̏I���������s��
	this->nowState->releaseProcess();

	// ��Ԃ̈ڍs������
	this->preState = this->nowState->getState();
	this->nowState = this->stateContainer.at(state_);
	this->nextState = nextState_;

	// ���݂̓����������s��
	this->nowState->insertProcess();

//	out << __FILE__ << ", " << __FUNCTION__ << endl;
	out << "preState = " << this->getStateString(this->preState) << endl;
	out << "nowState = " << this->getStateString(this->nowState->getState()) << endl;
	out << "nextState = " << this->getStateString(this->nextState) << endl;
	out << "message = " << this->messageForNext << endl;
}



/**----------------------------------------------------
 * @brief ���݂̏�Ԃ�\������
 *----------------------------------------------------*/
std::string LeagueModeManager::getStateString(ManagerState state_) const
{
	std::string state;

	switch (state_) {
		case MANAGERSTATE_INIT:
			state = "init";
			break;
		case MANAGERSTATE_TEAMSELECT:
			state = "TeamSelect";
			break;
		case MANAGERSTATE_GETDATA:
			state = "GetData";
			break;
		case MANAGERSTATE_GAME:
			state = "Game";
			break;
		case MANAGERSTATE_RESULT:
			state = "Result";
			break;
		case MANAGERSTATE_END:
			state = "End";
			break;
		default:
			state = "Invalid";
			break;
	}

	return state;
}



}    // namespace LeagueMode

