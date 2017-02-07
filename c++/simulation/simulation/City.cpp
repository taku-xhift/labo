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
 * @brief 初期化関数
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
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
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
 * @brief 初期化関数
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
 * @param[in]    rhs    データを代入する側
 * @return       変更を加えた本体
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
 * @brief 毎フレーム実行すること
 *---------------------------------------------------*/
void City::action()
{
	out << "My CityID is " << this->cityParameter.cityID << "." << endl;
	out << "Start Action!!!" << endl;

	this->battleWithTrooper();
	this->politicking();
}



/**----------------------------------------------------
 * @brief 派兵された兵士と戦闘
 * @note  実装がわかりにくいのでメモを。
 *          このモジュールの仕事は、
 *          troopers が空になるまで havingTeam と試合をし続ける。
 *          havingTeam が全て負けると再帰して
 *          troopers の最終勝利者を havingTeam にしなおして
 *          再度モジュールを実行する。
 *---------------------------------------------------*/
void City::battleWithTrooper()
{
	out << "Battle with Trooper." << endl;

	//-----------------------------------------------------
	//  まずは状況の整理
	//-----------------------------------------------------

	// 派兵された兵士がいなくなれば終了
	if (this->troopers.empty() == true) {
		out << "派兵されたグループがなくなりました。" << endl;
		return;
	}

	// 拠点に誰もいなかった場合
	//   (再帰ですでに防衛軍が全て倒された場合)
	if (this->havingTeam.empty() == true) {
		// とりあえず街の所属は最初の派遣軍のものに書き換え
		this->setParameterForGroup(this->troopers.front());
		this->troopers.erase(this->troopers.begin());

		// まだ派遣されている兵士が残っている場合
		if (this->troopers.empty() == false) {
			// group を見て仲間なら防衛軍に、そうでないなら
			// battle を開始するためにしたの処理に向かう
			while (this->manager.getTeamParameter(this->havingTeam.front()).group
				   != this->manager.getTeamParameter(this->troopers.front()).group)
			{
				this->havingTeam.push_back(*this->troopers.begin());
				this->troopers.erase(this->troopers.begin());

				// 残り派遣軍が０グループだった場合占拠してそのまま終了
				// １グループ以上いる場合は
				// 下の battle シーンに持ち込み
				if (this->troopers.empty() == true) {
					out << "占領されました。" << endl;
					return;
				}
			}   // while
		}   // if
	}   // if


	//-----------------------------------------------------
	//  以下が実際に battle の管理
	//    自分が所持している Team が負けるまで troopers と戦闘
	//    負けると戦闘の havingTeam が無くなり、消去される。
	//    havingTeam が残っているかチェックされ、なければループ終了
	//-----------------------------------------------------

	// 防衛軍が負けると false になるフラグ
	bool result = true;

	// 自分所持チーム用のコンテナを全て走査する
	while (this->havingTeam.empty() != true)
    {
		// チェックパラメータの初期化
		result = true;

		// 派兵されたチームのコンテナを全て走査する
		while (this->troopers.empty() != true)
		{
			result = this->manager.getWinner(this->havingTeam.front(), this->troopers.front());

			// 防衛軍の勝利
			if (result == true) {
				// 敗北したチームを勝利グループの使用可能リストに追加
				{
					TeamParameter teamPara = this->manager.getTeamParameter(this->havingTeam.front());
					UserData data = this->manager.getUserData(teamPara.group);
					data.getAlliancableTeam().push_back(this->troopers.front());
					this->manager.setUserData(data);
				}

				// 先頭の必要なくなったデータを消去
				this->troopers.pop_front();
			}
			// 防衛軍の敗北
			else {
				// 敗北したチームを勝利グループの使用可能リストに追加
				{
					TeamParameter teamPara = this->manager.getTeamParameter(this->troopers.front());
					UserData data = this->manager.getUserData(teamPara.group);
					data.getAlliancableTeam().push_back(this->havingTeam.front());
					this->manager.setUserData(data);
				}

				// 先頭の必要なくなったデータの消去
				this->havingTeam.pop_front();

				// ループからの脱出
				break;
			}
		}   // roop-troopIte
	}   // roop-teamIte

}


/**----------------------------------------------------
 * @brief 派兵
 *---------------------------------------------------*/
void City::troopDispatch()
{
	out << "Do Dispatch." << endl;


	// なんやかんやで派兵するかどうか判断した後
	// TODO

	int place = 0;
	std::list<int> team = this->troopers;

	// 派兵する
	this->manager.troopToCity(team.front(), place);
}


/**----------------------------------------------------
 * @brief 政治活動
 *---------------------------------------------------*/
void City::politicking()
{
	out << "Do politicking." << endl;

	// なんやかんやの政治活動
	this->troopDispatch();
}




/**----------------------------------------------------
* @brief      主に group に関連のあるパラメータのセッタ
* @param[in]  troopersID_    A parameter to set.
*---------------------------------------------------*/
void City::setParameterForGroup(int troopersID_) {
	this->cityParameter.group = this->manager.getTeamParameter(troopersID_).group;
}


}   // namespace NewMode

