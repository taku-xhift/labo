
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>

#include "GameManager.hpp"
#include "GameData.hpp"
#include "City.hpp"
#include "Team.hpp"
#include "StreamObject.hpp"


//-----------------------------------------------------
//  namespace
//-----------------------------------------------------
using namespace so;


namespace NewMode {

/**
 * @brief �X�p�����[�^�N���X
 *          �R���X�g���N�^�ŊX�̃p�����[�^�����Ă�����
 * @author  Takuya Shishido
 * @date    2009.10.20 23:05:43
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 */

/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
CityParameter::CityParameter()
	: level(0)
	, income(0)
	, node(0)
	, neighbor(0)
	, group(0)
	, power(0)
	, importance(0)
	, cityID(0)
{
	this->init();
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
CityParameter::~CityParameter()
{

}


/**----------------------------------------------------
 * @brief �������֐�
 *---------------------------------------------------*/
void CityParameter::init()
{
	this->level = 0;
	this->income = 0;
	this->node = 0;
	this->neighbor = 0;
	this->group = 0;
	this->power = 0;
	this->importance = 0;
	this->cityID = 0;
	this->name.clear();
}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    �f�[�^�������鑤
 * @return       �ύX���������{��
 *---------------------------------------------------*/
CityParameter& CityParameter::operator= (const CityParameter& rhs)
{
	this->level = rhs.level;
	this->income = rhs.income;
	this->node = rhs.node;
	this->neighbor = rhs.neighbor;
	this->group = rhs.group;
	this->power = rhs.power;
	this->importance = rhs.importance;
	this->cityID = rhs.cityID;
	this->name = rhs.name;

	return *this;
}


/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
City::City(GameManager& gameManager, const CityParameter& cityParameter_)
	: manager(gameManager)
	, cityParameter(cityParameter_)
{

}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
City::~City()
{

}


/**----------------------------------------------------
 * @brief �������֐�
 *---------------------------------------------------*/
void City::init()
{
	this->cityParameter.init();

	this->troopers.clear();
	this->losers.clear();
	this->havingTeam.clear();
	this->neighbor.clear();
}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    �f�[�^�������鑤
 * @return       �ύX���������{��
 *---------------------------------------------------*/
City& City::operator= (const City& rhs)
{
	this->manager = rhs.manager;

	this->cityParameter = rhs.cityParameter;
	this->losers = rhs.losers;
	this->havingTeam = rhs.havingTeam;
	this->neighbor = rhs.neighbor;

	return *this;
}



/**----------------------------------------------------
 * @brief ���t���[�����s���邱��
 *---------------------------------------------------*/
void City::action()
{
	out << "My CityID is " << this->cityParameter.cityID << "." << endl;
	out << "Start Action!!!" << endl;

	this->battleWithTrooper();
	this->politicking();
}



/**----------------------------------------------------
 * @brief �h�����ꂽ���m�Ɛ퓬
 * @note  �������킩��ɂ����̂Ń������B
 *          ���̃��W���[���̎d���́A
 *          troopers ����ɂȂ�܂� havingTeam �Ǝ�������������B
 *          havingTeam ���S�ĕ�����ƍċA����
 *          troopers �̍ŏI�����҂� havingTeam �ɂ��Ȃ�����
 *          �ēx���W���[�������s����B
 *---------------------------------------------------*/
void City::battleWithTrooper()
{
	out << "Battle with Trooper." << endl;

	//-----------------------------------------------------
	//  �܂��͏󋵂̐���
	//-----------------------------------------------------

	// �h�����ꂽ���m�����Ȃ��Ȃ�ΏI��
	if (this->troopers.empty() == true) {
		out << "�h�����ꂽ�O���[�v���Ȃ��Ȃ�܂����B" << endl;
		return;
	}

	// ���_�ɒN�����Ȃ������ꍇ
	//   (�ċA�ł��łɖh�q�R���S�ē|���ꂽ�ꍇ)
	if (this->havingTeam.empty() == true) {
		// �Ƃ肠�����X�̏����͍ŏ��̔h���R�̂��̂ɏ�������
		this->setParameterForGroup(this->troopers.front());
		this->troopers.erase(this->troopers.begin());

		// �܂��h������Ă��镺�m���c���Ă���ꍇ
		if (this->troopers.empty() == false) {
			// group �����Ē��ԂȂ�h�q�R�ɁA�����łȂ��Ȃ�
			// battle ���J�n���邽�߂ɂ����̏����Ɍ�����
			while (this->manager.getTeamParameter(this->havingTeam.front()).group
				   != this->manager.getTeamParameter(this->troopers.front()).group)
			{
				this->havingTeam.push_back(*this->troopers.begin());
				this->troopers.erase(this->troopers.begin());

				// �c��h���R���O�O���[�v�������ꍇ�苒���Ă��̂܂܏I��
				// �P�O���[�v�ȏア��ꍇ��
				// ���� battle �V�[���Ɏ�������
				if (this->troopers.empty() == true) {
					out << "��̂���܂����B" << endl;
					return;
				}
			}   // while
		}   // if
	}   // if


	//-----------------------------------------------------
	//  �ȉ������ۂ� battle �̊Ǘ�
	//    �������������Ă��� Team ��������܂� troopers �Ɛ퓬
	//    ������Ɛ퓬�� havingTeam �������Ȃ�A���������B
	//    havingTeam ���c���Ă��邩�`�F�b�N����A�Ȃ���΃��[�v�I��
	//-----------------------------------------------------

	// �h�q�R��������� false �ɂȂ�t���O
	bool result = true;

	// ���������`�[���p�̃R���e�i��S�đ�������
	while (this->havingTeam.empty() != true)
    {
		// �`�F�b�N�p�����[�^�̏�����
		result = true;

		// �h�����ꂽ�`�[���̃R���e�i��S�đ�������
		while (this->troopers.empty() != true)
		{
			result = this->manager.getWinner(this->havingTeam.front(), this->troopers.front());

			// �h�q�R�̏���
			if (result == true) {
				// �s�k�����`�[���������O���[�v�̎g�p�\���X�g�ɒǉ�
				{
					TeamParameter teamPara = this->manager.getTeamParameter(this->havingTeam.front());
					UserData data = this->manager.getUserData(teamPara.group);
					data.getAlliancableTeam().push_back(this->troopers.front());
					this->manager.setUserData(data);
				}

				// �擪�̕K�v�Ȃ��Ȃ����f�[�^������
				this->troopers.pop_front();
			}
			// �h�q�R�̔s�k
			else {
				// �s�k�����`�[���������O���[�v�̎g�p�\���X�g�ɒǉ�
				{
					TeamParameter teamPara = this->manager.getTeamParameter(this->troopers.front());
					UserData data = this->manager.getUserData(teamPara.group);
					data.getAlliancableTeam().push_back(this->havingTeam.front());
					this->manager.setUserData(data);
				}

				// �擪�̕K�v�Ȃ��Ȃ����f�[�^�̏���
				this->havingTeam.pop_front();

				// ���[�v����̒E�o
				break;
			}
		}   // roop-troopIte
	}   // roop-teamIte

}


/**----------------------------------------------------
 * @brief �h��
 *---------------------------------------------------*/
void City::troopDispatch()
{
	out << "Do Dispatch." << endl;


	// �Ȃ�₩���Ŕh�����邩�ǂ������f������
	// TODO

	int place = 0;
	std::list<int> team = this->troopers;

	// �h������
	this->manager.troopToCity(team.front(), place);
}


/**----------------------------------------------------
 * @brief ��������
 *---------------------------------------------------*/
void City::politicking()
{
	out << "Do politicking." << endl;

	// �Ȃ�₩���̐�������
	this->troopDispatch();
}




/**----------------------------------------------------
* @brief      ��� group �Ɋ֘A�̂���p�����[�^�̃Z�b�^
* @param[in]  troopersID_    A parameter to set.
*---------------------------------------------------*/
void City::setParameterForGroup(int troopersID_) {
	this->cityParameter.group = this->manager.getTeamParameter(troopersID_).group;
}


}   // namespace NewMode

