/**
 * @file
 * @brief インターフェース部分。
 * @note    これを介してＣ側ではデータのやり取りを行う。
 *
 * @author Takuya Shishido
 * @date 2010.04.07 14:37:55
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 14:37:55
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef RECIPROCATE_H_INCLUDED
#define RECIPROCATE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/DBError.h"


#ifdef __cplusplus
extern "C" {
#endif



/**-------------------------------------------------------------
 * @brief ID を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド（type=INT,value=playerNumber）
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError findPlayerData_by_Number(ReciprocateData* command_, PlayerData* data_);


/**-------------------------------------------------------------
 * @brief 名前を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド（type=STRING,value=playerName）
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError findPlayerData_by_PlayerName(ReciprocateData* command_, PlayerData* data_);


/**-------------------------------------------------------------
 * @brief チームの名前を頼りに、そのチームに所属する選手のデータ一覧を
 *              ＤＢ から取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド（type=string,value=teamName）
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError findPlayerDataByTeamName(ReciprocateData* command_, TeamData* data_);


/**-------------------------------------------------------------
 * @brief 試合結果を perl に渡す
 * @note    イメージ的にはこれの実装が perl とつながっている。
 * @param[in]       command_    コマンド（type=string,value=teamName）
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError sendGameResult(ReciprocateData* command_);


#ifdef __cplusplus
}
#endif



#endif

