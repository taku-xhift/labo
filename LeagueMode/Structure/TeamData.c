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
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"

/**----------------------------------------------------
 * @brief DataSet 型のデータから TeamData 型のデータを作り出す
 * @param[out]  team_       セット先
 * @param[in]   dataSet_    PlayerData が入っているデータ
 *---------------------------------------------------*/
//void setPlayerDataToTeamData(TeamData* teamData_, ReciprocateData* reciprocateData_)
//{
//	PlayerData* playerArray;
//	int i = 0;
//
//	assert(reciprocateData_);
//	if (reciprocateData_->type != DATATYPE_PLAYERDATA) {
//		assert(0);
//	}
//
//	team_->playerNumber = reciprocateData_->num;
//
//	for (i = 0; i < reciprocateData_->num; ++i) {
//		playerArray = (PlayerData*)reciprocateData_->value[i];
//		team_->players[i] = *playerArray;
//	}
//}


/**----------------------------------------------------
 * @brief チームのそう攻撃力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム攻撃力
 *---------------------------------------------------*/
int getTeamOffence(TeamData* teamData_)
{
	int offence = 0;
	int i = 0;

	assert(teamData_);

	for (i = 0; i < teamData_->playerNumber; ++i) {
		offence += teamData_->players[i].offence;
	}

	return offence;
}


/**----------------------------------------------------
 * @brief チームの総防御力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム防御力
 *---------------------------------------------------*/
int getTeamDefence(TeamData* teamData_)
{
	int defence = 0;
	int i = 0;

	assert(teamData_);

	for (i = 0; i < teamData_->playerNumber; ++i) {
		defence += teamData_->players[i].defence;
	}

	return defence;
}



