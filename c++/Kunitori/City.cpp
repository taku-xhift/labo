/**
 * @file
 * @brief 街モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.20 23:05:43
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


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
 * @brief 街パラメータクラス
 *          コンストラクタで街のパラメータをしていする
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
 * @brief 初期化関数
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
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
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
 * @brief 初期化関数
 *---------------------------------------------------*/
void City::init()
{
	this->cityParameter.init();

	this->havingTeam.clear();
}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
 *---------------------------------------------------*/
City& City::operator= (const City& rhs)
{
	this->manager = rhs.manager;

	this->havingTeam = rhs.havingTeam;

	return *this;
}



/**----------------------------------------------------
 * @brief 毎フレーム実行すること
 *---------------------------------------------------*/
void City::action()
{
	out << "My CityID is " << this->cityParameter.cityID << "." << endl;
	out << "Start Action!!!" << endl;
}


}   // namespace NewMode

