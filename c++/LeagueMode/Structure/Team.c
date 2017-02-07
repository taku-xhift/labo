/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 15:12:15
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Team.h"
#include "PlayerData.h"

/**----------------------------------------------------
 * @brief DataSet 型のデータから Team 型のデータを作り出す
 * @param[in]   dataSet_    データ
 * @return      変換された結果のデータ
 *---------------------------------------------------*/
Team convertFromDataSetToTeam(ReciprocateData* reciprocateData_)
{
	Team team;
	PlayerData* playerArray;
	int i = 0;

	assert(reciprocateData_);
	if (reciprocateData_->type != DATATYPE_PLAYERDATA) {
		assert(0);
	}

	team.playerNumber = reciprocateData_->num;

	for (i = 0; i < reciprocateData_->num; ++i) {
		playerArray = (PlayerData*)reciprocateData_->data[i];
		team.players[i] = *playerArray;
	}

	return team;
}


/**----------------------------------------------------
 * @brief チームのそう攻撃力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム攻撃力
 *---------------------------------------------------*/
int getTeamOffence(Team* team_)
{
	int offence = 0;
	int i = 0;

	assert(team_);

	for (i = 0; i < team_->playerNumber; ++i) {
		offence += team_->players[i].offence;
	}

	return offence;
}


/**----------------------------------------------------
 * @brief チームの総防御力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム防御力
 *---------------------------------------------------*/
int getTeamDefence(Team* team_)
{
	int defence = 0;
	int i = 0;

	assert(team_);

	for (i = 0; i < team_->playerNumber; ++i) {
		defence += team_->players[i].defence;
	}

	return defence;
}



