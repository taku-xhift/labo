/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 15:09:22
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 15:09:22
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PLAYERDATA_H_INCLUDED
#define PLAYERDATA_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"

//-----------------------------------------------------
//  declaration
//-----------------------------------------------------



/**
 * @brief 選手データまとめ
 * @note    cpp で使う際には PlayerDataForCpp を使う方がお勧め。出力をサポートしてもらえる。
 * @author  Takuya Shishido
 * @date    2010.04.02 15:09:22
 * @version 0.01, Shishido Takuya, 2010.04.02 15:09:22
 */
typedef struct
{
	char        name[0xff];     //!< 選手名
	int         entryNumber;    //!< 背番号
	int         offence;        //!< オフェンス
	int         defence;        //!< ディフェンス
} PlayerData;    // struct PlayerData



#endif

