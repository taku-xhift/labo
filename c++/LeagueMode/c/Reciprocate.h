/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.07 14:37:55
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 14:37:55
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef RECIPROCATE_H_INCLUDED
#define RECIPROCATE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "PlayerData.h"
#include "GameResult.h"


#ifdef __cplusplus
extern "C" {
#endif



/**-------------------------------------------------------------
 * @brief ID を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       ID_     選手の登録ＩＤ
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_Number(int ID_);


/**-------------------------------------------------------------
 * @brief 名前を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       name_   選手の名前
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_PlayerName(const char* name_);


/**-------------------------------------------------------------
 * @brief チームの名前を頼りに、そのチームに所属する選手のデータ一覧を
 *              ＤＢ から取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]   teamName_           キーワード
 * @param[out]  reciprocateData_    出力先
 *------------------------------------------------------------*/
void findPlayerData_by_TeamName(const char* teamName_, ReciprocateData* reciprocateData_);


/**-------------------------------------------------------------
 * @brief 試合結果を perl に渡す
 * @note    イメージ的にはこれの実装が perl とつながっている。
 * @param[in]   userID_         ユーザＩＤ。ユニーク。
 * @param[out]  gameResult_     試合結果
 *------------------------------------------------------------*/
void sendGameResult(int userID_, const GameResult* gameResult_);


#ifdef __cplusplus
}
#endif



#endif

