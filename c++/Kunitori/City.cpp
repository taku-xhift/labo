
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
	, group(0)
	, power(0)
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
	this->group = 0;
	this->power = 0;
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
	this->group = rhs.group;
	this->power = rhs.power;
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

	this->havingTeam.clear();
}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    �f�[�^�������鑤
 * @return       �ύX���������{��
 *---------------------------------------------------*/
City& City::operator= (const City& rhs)
{
	this->manager = rhs.manager;

	this->havingTeam = rhs.havingTeam;

	return *this;
}



/**----------------------------------------------------
 * @brief ���t���[�����s���邱��
 *---------------------------------------------------*/
void City::action()
{
	out << "My CityID is " << this->cityParameter.cityID << "." << endl;
	out << "Start Action!!!" << endl;
}


}   // namespace NewMode

