
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManager.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/StreamObject.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	const int teamNum = 2;  //!< �ΐ�Ɋւ��`�[����
}


//-----------------------------------------------------
//  function
//-----------------------------------------------------
namespace LeagueMode {

/**
 * @brief �������ꊇ���Đ��������t�@���N�^�B
 * @note    LeagueModeManager::run �̖߂�l�� RUNSTATE_FINISH �ɂȂ�܂�
 *              ���[�v����葱����̂Œ���
 *
 * @author Takuya Shishido
 * @date   2010-04-27
 * @version 0.01
*/
struct Functor_Execute
{

	/**----------------------------------------------------
	 * @brief constructor
	 * @param[in]   manager_    LeagueModeManager �{�́Brun ���Ăяo�����
	 *---------------------------------------------------*/
	explicit Functor_Execute(LeagueModeManager& manager_) : manager(manager_) {}



	/**----------------------------------------------------
	 * @brief �t�@���N�^�{��
	 * @note    �N���X�{�̂̐������悭�ǂނ���
	 * @param[in]   state_      �������e�̑I��
	 *---------------------------------------------------*/
	void operator()(ManagerState state_) {
		this->manager.setState(state_);
		while (this->manager.run() != RUNSTATE_FINISH) {
		}
	}

private:

	LeagueModeManager& manager;     //!< ���[�O���[�h�Ǘ��I�u�W�F�N�g
};

}    // namespace LeagueMode


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
	safeDelete(this->nowState);
}


/**----------------------------------------------------
 * @brief   ���s�֐�
 *              State Pattern �ŏ�����Ă��邽�߁A
 *              nowState �Ɉˑ����鏈�����s����B
 * @return  ���݂̏�Ԃ̖��O
 *----------------------------------------------------*/
RunState LeagueModeManager::run()
{
	// �o��
	this->opParameter();	// �Q�[���S�̂̏���

	RunState result = this->nowState->run();
	this->nowState->printout();     // �o�̓f�[�^

	// ���݂̏�Ԃ̏o��
	out << "Now State is " << this->getStateString(this->nowState->getState()) <<"!!!" << endl;

	// �f�[�^�֘A�̍X�V
	this->leagueWork.update();

	return result;
}


/**----------------------------------------------------
 * @brief �����Ŋ��蓖�Ă�ꂽ�d���݂̂��s��
 * @param[in]   state_          �������e�̎w��
 *----------------------------------------------------*/
void LeagueModeManager::executeModule(LeaugeModeManagerBehavior behavior_)
{
	//TODO
	switch (behavior_) {
	    case LEAGUEMODEMANAGERBEHAVIOR_TEAMSELECT: {
			LeagueMode::LeagueModeManager::getInstance()->behaviorTeamSelect();
			break;
		}
	    case LEAGUEMODEMANAGERBEHAVIOR_AUTOGAME: {
			// TODO
			//LeagueMode::LeagueModeManager::getInstance()->behaviorGame();
			break;
		}
		case LEAGUEMODEMANAGERBEHAVIOR_MAX:
		// �� through down
		default: {
			assert(0);
		}
	}
}


/**----------------------------------------------------
 * @brief  �f�[�^�o��
 * @note    �{�^�����������Ƃ��̂�
 *----------------------------------------------------*/
void LeagueModeManager::opParameter()
{
	out << "\n\n====================PrintStart====================" << endl;
	out << "nowState => " << this->getStateString(this->getNowState()) << endl;
	out << "preState => " << this->getStateString(this->preState) << endl;
}



/**----------------------------------------------------
 * @brief constructor
 *           Singleton Pattern �ɂ���Ă��邽�߁Aprivate �ȃR���X�g���N�^
 *----------------------------------------------------*/
LeagueModeManager::LeagueModeManager() : nowState(NULL)
{
	this->preState = MANAGERSTATE_FIRST;
	this->nowState = this->createState(MANAGERSTATE_FIRST);
	this->nextState = MANAGERSTATE_MAX;
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
	safeDelete(this->nowState);
	this->nowState = this->createState(state_);
	this->nextState = nextState_;

	// ���݂̓����������s��
	this->nowState->insertProcess();

	out << "preState = " << this->getStateString(this->preState) << endl;
	out << "nowState = " << this->getStateString(this->nowState->getState()) << endl;
	out << "nextState = " << this->getStateString(this->nextState) << endl;
	out << "message = " << this->messageForNext << endl;
}


/**----------------------------------------------------
 * @brief ���݂̏�Ԃ𕶎���Ŏ擾����
 * @return  ��Ԃ̕�����̐擪�|�C���^
 *----------------------------------------------------*/
const char* LeagueModeManager::getStateString(ManagerState state_) const
{
	const char* state;

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
		case MANAGERSTATE_RELEASE:
			state = "Release";
			break;
		case MANAGERSTATE_END:
			state = gameEnd;
			break;
		default:
			state = "Invalid";
			break;
	}

	return state;
}


/**----------------------------------------------------
 * @brief state_ �Ŏw�肳�ꂽ�f�[�^���쐬����
 * @param[in]   state_      �쐬���鏈��
 *----------------------------------------------------*/
StateBase* LeagueModeManager::createState(ManagerState state_)
{
	switch (state_) {
        case MANAGERSTATE_INIT: {
			return New InitState(*this, this->leagueWork);
		}
		case MANAGERSTATE_TEAMSELECT: {
			return New TeamSelectState(*this, this->leagueWork);
		}
        case MANAGERSTATE_GETDATA: {
			return New GetDataState(*this, this->leagueWork);
		}
        case MANAGERSTATE_GAME: {
			return New GameState(*this, this->leagueWork);
		}
        case MANAGERSTATE_RESULT: {
			return New ResultState(*this, this->leagueWork);
		}
        case MANAGERSTATE_RELEASE: {
			return New ReleaseState(*this, this->leagueWork);
		}
        case MANAGERSTATE_MAX:
		// �� through down
		default: {
			assert(0);
			return NULL;
		}
	}
}



/**----------------------------------------------------
 * @brief �`�[���Z���N�g�Ɋւ����A�̏������s��
 *----------------------------------------------------*/
void LeagueModeManager::behaviorTeamSelect()
{
	std::vector<ManagerState> list;
	list.push_back(MANAGERSTATE_INIT);
	list.push_back(MANAGERSTATE_TEAMSELECT);
	list.push_back(MANAGERSTATE_RELEASE);

	std::for_each(list.begin(), list.end(), Functor_Execute(*this));
}



/**----------------------------------------------------
 * @brief �������ʌv�Z�Ɋւ����A�̏������s��
 *----------------------------------------------------*/
void LeagueModeManager::behaviorGame(const char* homeTeam_, const char* awayTeam_)
{
	getInstance()->teamData.resize(2);
	strcpy(getInstance()->teamData.at(home).name, homeTeam_);
	strcpy(getInstance()->teamData.at(away).name, awayTeam_);

	std::vector<ManagerState> list;
	list.push_back(MANAGERSTATE_INIT);
	list.push_back(MANAGERSTATE_GETDATA);
	list.push_back(MANAGERSTATE_GAME);
	list.push_back(MANAGERSTATE_RESULT);
	list.push_back(MANAGERSTATE_RELEASE);

	std::for_each(list.begin(), list.end(), Functor_Execute(*getInstance()));
}




}    // namespace LeagueMode

