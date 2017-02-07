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
#include "PlayerData.h"
#include "LeagueModeDefineData.h"
#include "ReciprocateData.h"


/**
 * @brief チームデータを一塊にしたもの
 * @note    C++ で使う際には TeamForCpp がおすすめ。出力をサポートしてくれる。

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct {
	char            name[256];              //!< チーム名
	int             playerNumber;           //!< 実際に登録されている人数


	PlayerData      players[teamNumber];    //!< 選手
} Team;




/**
 * @note 以下、C++ 互換が必要なもの
 */
#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief DataSet 型のデータから Team 型のデータを作り出す
 * @param[in]   dataSet_    データ
 * @return      変換された結果のデータ
 *---------------------------------------------------*/
Team convertFromDataSetToTeam(ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief チームのそう攻撃力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム攻撃力
 *---------------------------------------------------*/
int getTeamOffence(Team* team_);


/**----------------------------------------------------
 * @brief チームの総防御力を取得する
 * @param[in]   team_   計算が必要なチーム
 * @return      チーム防御力
 *---------------------------------------------------*/
int getTeamDefence(Team* team_);



#ifdef __cplusplus
}
#endif


#endif

