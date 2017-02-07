/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 15:12:15
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


/**
 * @brief チームデータを一塊にしたもの
 * @note    C++ で使う際には TeamDataForCpp がおすすめ。出力をサポートしてくれる。

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct {
	char            name[256];                      //!< チーム名
	int             teamID;                         //!< チーム用ユニークＩＤ
	int             playerNumber;                   //!< 実際に登録されている人数
	PlayerData      players[team_playerNumber];     //!< 選手
} TeamData;




/**
 * @note 以下、C++ 互換が必要なもの
 */
#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief DataSet 型のデータから TeamData 型のデータを作り出す
 * @param[out]  team_       セット先
 * @param[in]   dataSet_    PlayerData が入っているデータ
 *---------------------------------------------------*/
void setPlayerDataToTeamData(TeamData* teamData_, ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief チームのそう攻撃力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム攻撃力
 *---------------------------------------------------*/
int getTeamOffence(TeamData* teamData_);


/**----------------------------------------------------
 * @brief チームの総防御力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム防御力
 *---------------------------------------------------*/
int getTeamDefence(TeamData* teamData_);



#ifdef __cplusplus
}
#endif


#endif

