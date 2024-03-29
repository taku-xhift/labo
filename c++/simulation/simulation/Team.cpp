
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Team.hpp"
#include "StreamObject.hpp"
#include "GameManager.hpp"


//-----------------------------------------------------
//  namespace
//-----------------------------------------------------
using namespace std;


namespace NewMode {

/**----------------------------------------------------
 * @brief  constructor
 *---------------------------------------------------*/
TeamParameter::TeamParameter()
	: rhythm(0)
	, stamina(0)
	, teamID(0)
	, warTimes(0)
	, winTimes(0)
	, group(0)
	, restTime(0)
	, homeTown(0)
	, contract(0)
{
	this->init();
}

/**----------------------------------------------------
 * @brief  destructor
 *---------------------------------------------------*/
TeamParameter::~TeamParameter()
{

}

/**----------------------------------------------------
 * @brief  初期化関数
 *---------------------------------------------------*/
void TeamParameter::init()
{
	this->rhythm = 0;
	this->stamina = 0;
	this->teamID = 0;
	this->warTimes = 0;
	this->winTimes = 0;
	this->group = 0;
	this->restTime = 0;
	this->homeTown = 0;
	this->contract = 0;
}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
 *---------------------------------------------------*/
TeamParameter& TeamParameter::operator= (const TeamParameter& rhs)
{
	this->rhythm = rhs.rhythm;
	this->stamina = rhs.stamina;
	this->teamID = rhs.teamID;
	this->warTimes = rhs.warTimes;
	this->winTimes = rhs.winTimes;
	this->group = rhs.group;
	this->restTime = rhs.restTime;
	this->homeTown = rhs.homeTown;
	this->contract = rhs.contract;
	this->name = rhs.name;

	return *this;
}



/**----------------------------------------------------
 * @brief  constructor
 *---------------------------------------------------*/
Team::Team(GameManager& gameManager_, const TeamParameter& teamParameter_)
	: gameManager(gameManager_)
	, teamParameter(teamParameter_)
	, power(0)
	, tiredness(0)
{

}


/**----------------------------------------------------
 * @brief  destructor
 *---------------------------------------------------*/
Team::~Team()
{

}


/**----------------------------------------------------
 * @brief      operator =
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
 *---------------------------------------------------*/
Team& Team::operator= (const Team& rhs)
{
	this->gameManager = rhs.gameManager;

	this->teamParameter = rhs.teamParameter;
	this->power = rhs.power;
	this->tiredness = rhs.tiredness;

	return *this;
}


/**----------------------------------------------------
 * @brief  初期化関数
 *---------------------------------------------------*/
void Team::init()
{
	this->teamParameter.init();

	this->power = 0;
	this->tiredness = 0;
}

/**----------------------------------------------------
 * @brief   battel with guardian
 * @retval  true    自分の勝利
 * @retval  false   相手の勝利
 *---------------------------------------------------*/
bool Team::battle(int battleTeamID)
{
	so::out << "myTeamID is " << this->teamParameter.teamID << "." << so::endl;
	so::out << "battleTeamID is " << battleTeamID << "." << so::endl;

	int myPower = this->getTeamBattlePower();
	int battleTeamPower = GameManager::getInstance().getTeamBattlePower(battleTeamID);

	return myPower > battleTeamPower;
}


}   // namespace NewMode

