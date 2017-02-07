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



//-----------------------------------------------------
//  local object
//-----------------------------------------------------
namespace {
	// input 格納先
	std::string input;
}



const TeamParameter& findAlliancableTeam() throw (Error::FindError)
{
	GameManager manager = GameManager::getInstance();

	// 番号で入力された場合
	int commandID = atoi(input.c_str());
	if (commandID > 0) {
		int ID = 0;
		int count = 0;

		// ランダムアクセスイテレータが std::list にはないため、
		// ループを回して指定された番号のデータを探し出す
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

	// チーム名で入力された場合
	else {
		// 名前から検索し、データを格納
		for (std::list<int>::const_iterator ite = manager.getUserData().getAlliancableTeam().begin();
			 ite != manager.getUserData().getAlliancableTeam().end();
			 ++ite)
		{
			// 名前が有効なものだった場合
			if (manager.getTeamParameter(*ite).name == input) {
				return manager.getTeamParameter(*ite);
			}
		}

		// 番号でも名前でも検索に引っかからなかった場合
		//      例外を送出して終了
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
 * @brief 初期化メソッド
 *---------------------------------------------------*/
void TurnStartState::init()
{
	this->commandContainer.clear();

	// ここでのデータの入れる順番と action 内の受付コマンドは
	//      同じ順番で入れること。順番が大事。
	this->commandContainer.push_back(STATEDATA_INVALID);                //!< 無効
	this->commandContainer.push_back(STATEDATA_TROOP);                  //!< 遠征
	this->commandContainer.push_back(STATEDATA_SIGNWITHTEAM);           //!< 契約
	this->commandContainer.push_back(STATEDATA_SHOWGROUPINFORMATION);   //!< グループ情報
	this->commandContainer.push_back(STATEDATA_SHOWTEAMINFORMATION);    //!< チーム情報
	this->commandContainer.push_back(STATEDATA_SHOWCITYINFORMATION);    //!< 街情報
	this->commandContainer.push_back(STATEDATA_TURNFOLLOWINGUSER);      //!< ターン終了
	this->commandContainer.push_back(STATEDATA_ENDGAME);                //!< ゲーム終了
	this->commandContainer.push_back(STATEDATA_TURNSTART);              //!< ターンスタート
}


/**----------------------------------------------------
 * @brief execute function
 *---------------------------------------------------*/
void TurnStartState::action()
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
 * @brief グループ情報表示のメソッド
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
	out << "グループの情報です" << endl;
	out << this->getManager().getUserData() << endl;

	out << "Return を押してください" << endl;
	std::cin >> input;

	this->getManager().setState(STATEDATA_TURNSTART);
}




/**----------------------------------------------------
 * @brief チーム情報を見せるためのメソッド
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

	out << "チーム情報を取得します。" << endl;
	out << "見たいチームの ID か名前を入力してください。" << endl;
	out << "入力可能範囲 : " << "0 → " << this->getManager().teamContainer.size() << endl;

	// チームネーム一覧出力
	for (unsigned int i = 0; i < this->getManager().teamContainer.size(); ++i) {
		out << "チームネーム : " << this->getManager().getTeamParameter(i).name << endl;
	}

	std::cin >> input;

	// 番号で入力された場合
	if (atoi(input.c_str()) < 0) {
		out << this->getManager().teamContainer.at(atoi(input.c_str())).getTeamParameter() << endl;
		this->getManager().setState(STATEDATA_TURNSTART);
	}

	// チーム名で入力された場合
	else {
		// 名前から検索し、データを出力
		for (std::vector<Team>::iterator ite = this->getManager().teamContainer.begin();
			 ite != this->getManager().teamContainer.end();
			 ++ite)
		{
			// 名前が有効なものだった場合
			if (ite->getTeamParameter().name == input) {
				out << *ite << endl;
				this->getManager().setState(STATEDATA_TURNSTART);
			}

			// 無効な入力だった場合
			else {
				out << "有効なデータを入力してください" << endl;
			}
		}
	}

}




/**----------------------------------------------------
 * @brief 街情報を見せるためのメソッド
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

	out << "街の情報を取得します。" << endl;
	out << "見たい街の ID か名前を入力してください。" << endl;
	out << "入力可能範囲 : " << "0 → " << this->getManager().cityContainer.size() << endl;

	int count = 0;

	// チームネーム一覧出力
	for (unsigned int i = 0; i < this->getManager().teamContainer.size(); ++i) {
		out << count << ". " << this->getManager().cityContainer.at(i).getCityParameter().name << endl;
	}

	std::cin >> input;

	// 番号で入力された場合
	if (atoi(input.c_str()) > 0) {
		out << this->getManager().cityContainer.at(atoi(input.c_str())).getCityParameter() << endl;
		this->getManager().setState(STATEDATA_TURNSTART);
	}

	// チーム名で入力された場合
	else {
		// 名前から検索し、データを出力
		for (std::vector<City>::iterator ite = this->getManager().cityContainer.begin();
			 ite != this->getManager().cityContainer.end();
			 ++ite)
		{
			// 名前が有効なものだった場合
			if (ite->getCityParameter().name == input) {
				out << *ite << endl;
				this->getManager().setState(STATEDATA_TURNSTART);
			}

			// 無効な入力だった場合
			else {
				out << "有効なデータを入力してください" << endl;
			}
		}
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

	int count = 0;
	TeamParameter allianceTeam;

	for (std::list<int>::const_iterator ite = this->getManager().getUserData().getAlliancableTeam().begin();
		 ite != this->getManager().getUserData().getAlliancableTeam().end();
		 ++ite)
	{
		// 契約可能チームの情報確保
		allianceTeam = this->getManager().getTeamParameter(*ite);

		out << count << ". " << allianceTeam.name << "    "
			<< "$" << allianceTeam.contract << endl;
	}

	out << " TOP にもどる場合は exit を入力してください" << endl;

	out << endl;
	out << "契約したいチームを入力してください" << endl;

	this->getManager().setState(STATEDATA_SIGNWITHTEAM);

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
	{
		// 一時データを作成
		UserData::AlliancableList list = this->getManager().getUserData().getAlliancableTeam();

		// 契約可能なチームが存在しなかった場合
		if (list.size() == 0) {
			out << "契約可能なチームが存在しませんでした。" << endl;
			this->getManager().setState(STATEDATA_TURNSTART);
			return;

		// 存在した場合は番号と名前の出力
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

			out << "番号を入力してください。" << endl;
			out << "(exit == 戻る)" << endl;
		}
	}

	//-----------------------------------------------------
	//  入力された情報が有効かどうか判定
	//-----------------------------------------------------
	TeamParameter allianceTeamPara;
	try {
		allianceTeamPara = findAlliancableTeam();
	} catch (...) {
		// ID や名前に引っかからなかった場合
		//  exit 入力だった
		if (input == Define::exit) {
			this->getManager().setState(STATEDATA_TURNSTART);
			return;
		} else {
			out << "有効なデータを入力してください" << endl;
			return;
		}
	}

	//-----------------------------------------------------
	//  上記が有効だった場合に
	//      契約可能かどうか判定
	//-----------------------------------------------------
	if ((this->getManager().getUserData().getMoney() - allianceTeamPara.contract) < 0) {
		out << "所持金が足りないため契約出来ません" << endl;
		this->getManager().setState(STATEDATA_SHOWALLIANCABLETEAM);
		return;
	}

	out << "契約しますがよろしいですか？ (yes/no)" << endl;

	std::cin >> input;

	// yes に関する文字を入力したと思われる場合
	if (input.find("y", 0) != std::string::npos) {
		// 一時データ
		UserData data = this->getManager().getUserData();
		// 変更データまとめ
		data.reduceMoney(allianceTeamPara.contract);
		data.addHavingteam(allianceTeamPara.teamID);

		// データの格納
		this->getManager().setUserData(data);
	}

	// それ以外は全てキャンセル
	else {
		out << "キャンセルされました" << endl;
		this->getManager().setState(STATEDATA_SHOWALLIANCABLETEAM);
	}

}




/**----------------------------------------------------
 * @brief 次のユーザにターンを回す
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


