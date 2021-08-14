
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



const TeamParameter& findAlliancableTeam() throw (Error::FindError)
{
	GameManager manager = GameManager::getInstance();

	// �ԍ��œ��͂��ꂽ�ꍇ
	int commandID = atoi(input.c_str());
	if (commandID > 0) {
		int ID = 0;
		int count = 0;

		// �����_���A�N�Z�X�C�e���[�^�� std::list �ɂ͂Ȃ����߁A
		// ���[�v���񂵂Ďw�肳�ꂽ�ԍ��̃f�[�^��T���o��
		for (std::list<int>::const_iterator ite = manager.getUserData().getAlliancableTeam().begin();
			 ite != manager.getUserData().getAlliancableTeam().end();
			 ++ite)
		{
			if (count == commandID) {
				ID = *ite;
			}
			++count;
		}
		return manager.getTeamParameter(ID);
	}

	// �`�[�����œ��͂��ꂽ�ꍇ
	else {
		// ���O���猟�����A�f�[�^���i�[
		for (std::list<int>::const_iterator ite = manager.getUserData().getAlliancableTeam().begin();
			 ite != manager.getUserData().getAlliancableTeam().end();
			 ++ite)
		{
			// ���O���L���Ȃ��̂������ꍇ
			if (manager.getTeamParameter(*ite).name == input) {
				return manager.getTeamParameter(*ite);
			}
		}

		// �ԍ��ł����O�ł������Ɉ���������Ȃ������ꍇ
		//      ��O�𑗏o���ďI��
		throw Error::FindError();
	}
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
TurnStartState::TurnStartState(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{
	this->init();
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
TurnStartState::~TurnStartState()
{

}


/**----------------------------------------------------
 * @brief ���������\�b�h
 *---------------------------------------------------*/
void TurnStartState::init()
{
	this->commandContainer.clear();

	// �����ł̃f�[�^�̓���鏇�Ԃ� action ���̎�t�R�}���h��
	//      �������Ԃœ���邱�ƁB���Ԃ��厖�B
	this->commandContainer.push_back(STATEDATA_INVALID);                //!< ����
	this->commandContainer.push_back(STATEDATA_TROOP);                  //!< ����
	this->commandContainer.push_back(STATEDATA_SIGNWITHTEAM);           //!< �_��
	this->commandContainer.push_back(STATEDATA_SHOWGROUPINFORMATION);   //!< �O���[�v���
	this->commandContainer.push_back(STATEDATA_SHOWTEAMINFORMATION);    //!< �`�[�����
	this->commandContainer.push_back(STATEDATA_SHOWCITYINFORMATION);    //!< �X���
	this->commandContainer.push_back(STATEDATA_TURNFOLLOWINGUSER);      //!< �^�[���I��
	this->commandContainer.push_back(STATEDATA_ENDGAME);                //!< �Q�[���I��
	this->commandContainer.push_back(STATEDATA_TURNSTART);              //!< �^�[���X�^�[�g
}


/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void TurnStartState::action()
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
 * @brief �O���[�v���\���̃��\�b�h
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
ShowGroupInformation::ShowGroupInformation(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
ShowGroupInformation::~ShowGroupInformation()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void ShowGroupInformation::action()
{
	out << "�O���[�v�̏��ł�" << endl;
	out << this->getManager().getUserData() << endl;

	out << "Return �������Ă�������" << endl;
	std::cin >> input;

	this->getManager().setState(STATEDATA_TURNSTART);
}




/**----------------------------------------------------
 * @brief �`�[�����������邽�߂̃��\�b�h
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
ShowTeamInformation::ShowTeamInformation(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
ShowTeamInformation::~ShowTeamInformation()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void ShowTeamInformation::action()
{

	out << "�`�[�������擾���܂��B" << endl;
	out << "�������`�[���� ID �����O����͂��Ă��������B" << endl;
	out << "���͉\�͈� : " << "0 �� " << this->getManager().teamContainer.size() << endl;

	// �`�[���l�[���ꗗ�o��
	for (unsigned int i = 0; i < this->getManager().teamContainer.size(); ++i) {
		out << "�`�[���l�[�� : " << this->getManager().getTeamParameter(i).name << endl;
	}

	std::cin >> input;

	// �ԍ��œ��͂��ꂽ�ꍇ
	if (atoi(input.c_str()) < 0) {
		out << this->getManager().teamContainer.at(atoi(input.c_str())).getTeamParameter() << endl;
		this->getManager().setState(STATEDATA_TURNSTART);
	}

	// �`�[�����œ��͂��ꂽ�ꍇ
	else {
		// ���O���猟�����A�f�[�^���o��
		for (std::vector<Team>::iterator ite = this->getManager().teamContainer.begin();
			 ite != this->getManager().teamContainer.end();
			 ++ite)
		{
			// ���O���L���Ȃ��̂������ꍇ
			if (ite->getTeamParameter().name == input) {
				out << *ite << endl;
				this->getManager().setState(STATEDATA_TURNSTART);
			}

			// �����ȓ��͂������ꍇ
			else {
				out << "�L���ȃf�[�^����͂��Ă�������" << endl;
			}
		}
	}

}




/**----------------------------------------------------
 * @brief �X���������邽�߂̃��\�b�h
 * @author  Takuya Shishido
 * @date    2009.10.27 23:42:36
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
ShowCityInformation::ShowCityInformation(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
ShowCityInformation::~ShowCityInformation()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void ShowCityInformation::action()
{

	out << "�X�̏����擾���܂��B" << endl;
	out << "�������X�� ID �����O����͂��Ă��������B" << endl;
	out << "���͉\�͈� : " << "0 �� " << this->getManager().cityContainer.size() << endl;

	int count = 0;

	// �`�[���l�[���ꗗ�o��
	for (unsigned int i = 0; i < this->getManager().teamContainer.size(); ++i) {
		out << count << ". " << this->getManager().cityContainer.at(i).getCityParameter().name << endl;
	}

	std::cin >> input;

	// �ԍ��œ��͂��ꂽ�ꍇ
	if (atoi(input.c_str()) > 0) {
		out << this->getManager().cityContainer.at(atoi(input.c_str())).getCityParameter() << endl;
		this->getManager().setState(STATEDATA_TURNSTART);
	}

	// �`�[�����œ��͂��ꂽ�ꍇ
	else {
		// ���O���猟�����A�f�[�^���o��
		for (std::vector<City>::iterator ite = this->getManager().cityContainer.begin();
			 ite != this->getManager().cityContainer.end();
			 ++ite)
		{
			// ���O���L���Ȃ��̂������ꍇ
			if (ite->getCityParameter().name == input) {
				out << *ite << endl;
				this->getManager().setState(STATEDATA_TURNSTART);
			}

			// �����ȓ��͂������ꍇ
			else {
				out << "�L���ȃf�[�^����͂��Ă�������" << endl;
			}
		}
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

	int count = 0;
	TeamParameter allianceTeam;

	for (std::list<int>::const_iterator ite = this->getManager().getUserData().getAlliancableTeam().begin();
		 ite != this->getManager().getUserData().getAlliancableTeam().end();
		 ++ite)
	{
		// �_��\�`�[���̏��m��
		allianceTeam = this->getManager().getTeamParameter(*ite);

		out << count << ". " << allianceTeam.name << "    "
			<< "$" << allianceTeam.contract << endl;
	}

	out << " TOP �ɂ��ǂ�ꍇ�� exit ����͂��Ă�������" << endl;

	out << endl;
	out << "�_�񂵂����`�[������͂��Ă�������" << endl;

	this->getManager().setState(STATEDATA_SIGNWITHTEAM);

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
	{
		// �ꎞ�f�[�^���쐬
		UserData::AlliancableList list = this->getManager().getUserData().getAlliancableTeam();

		// �_��\�ȃ`�[�������݂��Ȃ������ꍇ
		if (list.size() == 0) {
			out << "�_��\�ȃ`�[�������݂��܂���ł����B" << endl;
			this->getManager().setState(STATEDATA_TURNSTART);
			return;

		// ���݂����ꍇ�͔ԍ��Ɩ��O�̏o��
		} else {
			int count = 0;
			TeamParameter teamPara;

			for (UserData::AlliancableListIte listIte = list.begin();
				 listIte != list.end();
				 ++listIte)
			{
				teamPara = this->getManager().getTeamParameter(*listIte);
				out << count << ". " << teamPara.name << endl;
			}

			out << "�ԍ�����͂��Ă��������B" << endl;
			out << "(exit == �߂�)" << endl;
		}
	}

	//-----------------------------------------------------
	//  ���͂��ꂽ��񂪗L�����ǂ�������
	//-----------------------------------------------------
	TeamParameter allianceTeamPara;
	try {
		allianceTeamPara = findAlliancableTeam();
	} catch (...) {
		// ID �▼�O�Ɉ���������Ȃ������ꍇ
		//  exit ���͂�����
		if (input == Define::exit) {
			this->getManager().setState(STATEDATA_TURNSTART);
			return;
		} else {
			out << "�L���ȃf�[�^����͂��Ă�������" << endl;
			return;
		}
	}

	//-----------------------------------------------------
	//  ��L���L���������ꍇ��
	//      �_��\���ǂ�������
	//-----------------------------------------------------
	if ((this->getManager().getUserData().getMoney() - allianceTeamPara.contract) < 0) {
		out << "������������Ȃ����ߌ_��o���܂���" << endl;
		this->getManager().setState(STATEDATA_SHOWALLIANCABLETEAM);
		return;
	}

	out << "�_�񂵂܂�����낵���ł����H (yes/no)" << endl;

	std::cin >> input;

	// yes �Ɋւ��镶������͂����Ǝv����ꍇ
	if (input.find("y", 0) != std::string::npos) {
		// �ꎞ�f�[�^
		UserData data = this->getManager().getUserData();
		// �ύX�f�[�^�܂Ƃ�
		data.reduceMoney(allianceTeamPara.contract);
		data.addHavingteam(allianceTeamPara.teamID);

		// �f�[�^�̊i�[
		this->getManager().setUserData(data);
	}

	// ����ȊO�͑S�ăL�����Z��
	else {
		out << "�L�����Z������܂���" << endl;
		this->getManager().setState(STATEDATA_SHOWALLIANCABLETEAM);
	}

}




/**----------------------------------------------------
 * @brief ���̃��[�U�Ƀ^�[������
 * @author  Takuya Shishido
 * @date    2009.11.01 18:35
 * @version 0.01, Shishido Takuya, 2009.11.01 18:35
 ----------------------------------------------------*/
/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
TurnFollowingUser::TurnFollowingUser(GameManager& manager_, StateData stateData_)
	: State(manager_, stateData_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
TurnFollowingUser::~TurnFollowingUser()
{

}

/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void TurnFollowingUser::action()
{
	this->getManager().setNextUser();
	this->getManager().setState(STATEDATA_TURNSTART);
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


