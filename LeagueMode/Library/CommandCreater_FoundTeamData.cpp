/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.22 13:19:35
 *
 * @version 0.01, Shishido Takuya, 2010.04.22 13:19:35
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <climits>
#include <malloc.h>
#include <assert.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/CommandCreater_FoundTeamData.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Storage.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief 初期化されたコマンドの取得関数
 * @return      初期化されたコマンド
 *---------------------------------------------------*/
FoundTeamDataDirection getFoundTeamDataDirection()
{
	FoundTeamDataDirection direction;
	direction.teamName = "";
	direction.teamID = INT_MAX;

	for (int i = 0; i < sizeof(direction.useList)/sizeof(direction.useList[0]); ++i) {
		direction.useList[i] = USELIST_UNUSE;
	}

	return direction;
}


/**----------------------------------------------------
 * @brief パラメータセットモジュール
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @param[in]   teamID_     チームID
 *---------------------------------------------------*/
void setTeamID_FoundTeamDataDirection(FoundTeamDataDirection* command_, int teamID_)
{
	command_->teamID = teamID_;
	command_->useList[0] = USELIST_USE;
}


/**----------------------------------------------------
 * @brief パラメータセットモジュール
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @param[in]   teamName_   チーム名
 *---------------------------------------------------*/
void setTeanName_FoundTeamDataDirection(FoundTeamDataDirection* command_, const char* teamName_)
{
	command_->teamName = teamName_;
	command_->useList[1] = USELIST_USE;
}


/**----------------------------------------------------
 * @brief コマンド作成関数
 * @note    取得したコマンドは自分で解放関数を使って解放すること
 * @param[in]   指示
 * @return      作成されたコマンド
 *---------------------------------------------------*/
ReciprocateData* commandCreate_FoundTeamData(FoundTeamDataDirection* direction_)
{
	ReciprocateData* command = reinterpret_cast<ReciprocateData*>(calloc(1, sizeof(ReciprocateData)));

	command->type = DATATYPE_STRUCT;
	command->key = key_TeamData;

	// 要素数を数える
	int useCount = 0;
	for (int i = 0; i < sizeof(direction_->useList)/sizeof(direction_->useList[0]); ++i) {
		if (direction_->useList[i] == USELIST_USE) {
			++useCount;
		}
	}
	command->num = useCount;

	if (direction_->useList[0] = USELIST_USE) {
		command->value = reinterpret_cast<void**>(calloc(command->num, sizeof(void**)));
		command->value[useCount-1] = storage_Int(direction_->teamID, key_TeamData_ID);
		--useCount;
	}

	if (direction_->useList[1] == USELIST_USE) {
		command->value = reinterpret_cast<void**>(calloc(command->num, sizeof(void**)));
		command->value[useCount-1] = storage_String(direction_->teamName, key_TeamData_name);
		--useCount;
	}

	if (useCount != 0) {
		// 正しい数が処理されなかった
		assert(0);
	}

	return command;
}




