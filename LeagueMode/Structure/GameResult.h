/**
 * @file
 * @brief 試合の結果に関するデータを操作するメソッド
 *
 * @author Takuya Shishido
 * @date   2010.04.07 15:06:36
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 15:06:36
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GAMERESULT_H_INCLUDED
#define GAMERESULT_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <time.h>

typedef enum
{
	GAMERESULTCATEGORY_WIN,
	GAMERESULTCATEGORY_LOSE,
	GAMERESULTCATEGORY_PKWIN,
	GAMERESULTCATEGORY_PKLOSE,
	GAMERESULTCATEGORY_INVALID,
	GAMERESULTCATEGORY_MAX,
} GameResultCategory;



/**
 * @brief 試合結果を保存しておく構造体
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 15:06:36
 * @version 0.01, Shishido Takuya, 2010.04.07 15:06:36
 */
typedef struct
{
	int     adversaryID;    //!< 対戦相手のユーザＩＤ
	time_t  time;           //!< 試合開始時間
	int     teamID;         //!< 使用したチームのＩＤ
	int     victory;        //!< 勝ったら 1 、負けたら 0 、切断など無効なら -1
	int     goal;           //!< 得点
	int     loss;           //!< 得点

} GameResult;    // struct GameResult

#endif

