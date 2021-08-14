
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <cstdio>
#include "GameManager.hpp"
#include "State.hpp"
#include "StreamObject.hpp"
#include "Error.hpp"



using namespace so;

namespace NewMode {

//-----------------------------------------------------
//  local object
//-----------------------------------------------------
namespace {
	// input �i�[��
	std::string input;
}

/**----------------------------------------------------
 * @brief State Module
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
State::State(GameManager& manager_, StateData stateData_)
	: manager(manager_)
	, stateData(stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
State::~State()
{

}



/**----------------------------------------------------
* @brief �������̂��߂̃X�e�[�g
* @author  Takuya Shishido
* @date    2009/11/08 15:46
* @version 0.01, Shishido Takuya, 2009/11/08 15:46
----------------------------------------------------*/
/**----------------------------------------------------
* @brief execute function
*---------------------------------------------------*/
void InitState::action()
{
	bool check = false;
	int playerNum = 0;

	// ���͂��s���̊� check �� false
	while (!check) {
		out << "�Q�[���ɎQ������v���C���[�̐��𔼊p�����œ��͂��Ă�������" << endl;
		std::cin >> input;

		playerNum = atoi(input.c_str());
		if (playerNum <= 0) {
			out << "�L���ȃf�[�^����͂��Ă�������" << endl;
		} else if (playerNum > 20) {
			out << "�l�����������܂��B" << endl;
			out << "�L���ȃf�[�^����͂��Ă�������" << endl;
		} else {
			out << playerNum << "�l�ŃQ�[�����J�n���܂��B" << endl;
			check = true;
		}
	}

	this->getManager().init(playerNum);
}




/**----------------------------------------------------
 * @brief �^�[���̎n�߂̓��̓��W���[��
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
OrdinaryState::OrdinaryState(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{
	this->init();
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
OrdinaryState::~OrdinaryState()
{

}


/**----------------------------------------------------
 * @brief ���������\�b�h
 *---------------------------------------------------*/
void OrdinaryState::init()
{
	this->commandContainer.clear();

	// �����ł̃f�[�^�̓���鏇�Ԃ� action ���̎�t�R�}���h��
	//      �������Ԃœ���邱�ƁB���Ԃ��厖�B
	this->commandContainer.push_back(STATEDATA_INVALID);                //!< ����
	this->commandContainer.push_back(STATEDATA_SIGNWITHTEAM);           //!< �_��
	this->commandContainer.push_back(STATEDATA_ENDGAME);                //!< �Q�[���I��
}


/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void OrdinaryState::action()
{
	// �R�}���h�� 1 �Ԃ���B
	// 0 �Ԃ͉������͂���Ȃ������ꍇ�Ɏ󂯎��f�[�^�Ȃ̂�
	// �����������Ɩʓ|

	int commandCount = 1;

	out << "\n\n\n" << endl;
	out << "Command ?" << endl;
	out << commandCount++ << ". ����" << endl;
	out << commandCount++ << ". �`�[���ƌ_�񂷂�" << endl;
	out << commandCount++ << ". �O���[�v��������" << endl;
	out << commandCount++ << ". �`�[����������" << endl;
	out << commandCount++ << ". �e�X�̏�������" << endl;
	out << commandCount++ << ". �^�[���I��" << "\n" << endl;
	out << commandCount++ << ". �Q�[���I��" << "\n" << endl;

	out << "�Ή����鐔���𔼊p�œ��͂��Ă�������" << endl;

	std::cin >> input;

	int commandNumber = atoi(input.c_str());


	// ���͂��ꂽ�ԍ��ɉ����ď����N���X�ύX
	switch (commandNumber) {
	case COMMAND_INVALID:
		out << "�L���ȃf�[�^����͂��Ă�������" << endl;
		break;
	case COMMAND_TROOP:
		out << "�܂���������Ă��܂���" << endl;
		break;
	case COMMAND_SIGN_WITH_A_TEAM:
	case COMMAND_GROUP_INFORMATION:
	case COMMAND_TEAM_INFORMATION:
	case COMMAND_CITY_INFORMATION:
	case COMMAND_END_TURN:
	case COMMAND_END_GAME:
		this->getManager().setState(this->commandContainer.at(commandNumber));
		break;
	default:
		out << "�����ȃX�e�[�g���w�肳��܂���" << endl;
		break;
	}
}




/**----------------------------------------------------
 * @brief �_��\�ȃ`�[����\�����郁�\�b�h
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
ShowAlliancableTeam::ShowAlliancableTeam(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
ShowAlliancableTeam::~ShowAlliancableTeam()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void ShowAlliancableTeam::action()
{
	out << "�_��\�ȃ`�[��" << endl;

}



/**----------------------------------------------------
 * @brief �`�[���ƌ_�񂷂郁�\�b�h
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
SignWithTeam::SignWithTeam(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
SignWithTeam::~SignWithTeam()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void SignWithTeam::action()
{
	//-----------------------------------------------------
	//  �_�񂷂�`�[���̗L���ŏ�����ύX
	//-----------------------------------------------------


	//-----------------------------------------------------
	//  ���͂��ꂽ��񂪗L�����ǂ�������
	//-----------------------------------------------------

	//-----------------------------------------------------
	//  ��L���L���������ꍇ��
	//      �_��\���ǂ�������
	//-----------------------------------------------------

}







/**----------------------------------------------------
 * @brief �Q�[���̏I�����Ǘ�
 * @author  Takuya Shishido
 * @date    2009.11.01 18:46
 * @version 0.01, Shishido Takuya, 2009.11.01 18:46
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
EndGame::EndGame(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
EndGame::~EndGame()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void EndGame::action()
{

}


}   // namespace NewMode


