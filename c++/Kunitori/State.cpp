/**
 * @file
 * @brief GameManager の振る舞いを決める状態モジュール群
 *
 * @author Takuya Shishido
 * @date 2009.10.27 23:42:36
 *
 * @version 0.01, Shishido Takuya, 2009.10.27 23:42:36
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


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
	// input 格納先
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
* @brief 初期化のためのステート
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

	// 入力が不正の間 check は false
	while (!check) {
		out << "ゲームに参加するプレイヤーの数を半角数字で入力してください" << endl;
		std::cin >> input;

		playerNum = atoi(input.c_str());
		if (playerNum <= 0) {
			out << "有効なデータを入力してください" << endl;
		} else if (playerNum > 20) {
			out << "人数が多すぎます。" << endl;
			out << "有効なデータを入力してください" << endl;
		} else {
			out << playerNum << "人でゲームを開始します。" << endl;
			check = true;
		}
	}

	this->getManager().init(playerNum);
}




/**----------------------------------------------------
 * @brief ターンの始めの入力モジュール
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
 * @brief 初期化メソッド
 *---------------------------------------------------*/
void OrdinaryState::init()
{
	this->commandContainer.clear();

	// ここでのデータの入れる順番と action 内の受付コマンドは
	//      同じ順番で入れること。順番が大事。
	this->commandContainer.push_back(STATEDATA_INVALID);                //!< 無効
	this->commandContainer.push_back(STATEDATA_SIGNWITHTEAM);           //!< 契約
	this->commandContainer.push_back(STATEDATA_ENDGAME);                //!< ゲーム終了
}


/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void OrdinaryState::action()
{
	// コマンドは 1 番から。
	// 0 番は何も入力されなかった場合に受け取るデータなので
	// それを許可すると面倒

	int commandCount = 1;

	out << "\n\n\n" << endl;
	out << "Command ?" << endl;
	out << commandCount++ << ". 遠征" << endl;
	out << commandCount++ << ". チームと契約する" << endl;
	out << commandCount++ << ". グループ情報を見る" << endl;
	out << commandCount++ << ". チーム情報を見る" << endl;
	out << commandCount++ << ". 各街の情報を見る" << endl;
	out << commandCount++ << ". ターン終了" << "\n" << endl;
	out << commandCount++ << ". ゲーム終了" << "\n" << endl;

	out << "対応する数字を半角で入力してください" << endl;

	std::cin >> input;

	int commandNumber = atoi(input.c_str());


	// 入力された番号に応じて処理クラス変更
	switch (commandNumber) {
	case COMMAND_INVALID:
		out << "有効なデータを入力してください" << endl;
		break;
	case COMMAND_TROOP:
		out << "まだ実装されていません" << endl;
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
		out << "無効なステートを指定されました" << endl;
		break;
	}
}




/**----------------------------------------------------
 * @brief 契約可能なチームを表示するメソッド
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
	out << "契約可能なチーム" << endl;

}



/**----------------------------------------------------
 * @brief チームと契約するメソッド
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
	//  契約するチームの有無で処理を変更
	//-----------------------------------------------------


	//-----------------------------------------------------
	//  入力された情報が有効かどうか判定
	//-----------------------------------------------------

	//-----------------------------------------------------
	//  上記が有効だった場合に
	//      契約可能かどうか判定
	//-----------------------------------------------------

}







/**----------------------------------------------------
 * @brief ゲームの終了を管理
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


