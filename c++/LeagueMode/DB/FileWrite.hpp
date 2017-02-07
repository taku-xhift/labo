/**
 * @file
 * @brief ファイルに書き込む処理。本来は perl が行う仕事
 *
 * @author Takuya Shishido
 * @date   2010.04.07 16:07:26
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 16:07:26
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef FILEWRITE_HPP_INCLUDED
#define FILEWRITE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "../GameResult.h"


#ifdef __cplusplus
extern "C" {
#endif

/**-------------------------------------------------------------
 * @brief 試合の結果をファイルに書き出し。
 * @param[in]   userID_     試合を行ったユーザのＩＤ
 * @param[in]   gameResult  試合結果
 *-------------------------------------------------------------*/
void writeFile_GameResult(int userID_, const GameResult* gameResult_);

#ifdef __cplusplus
}
#endif


#endif

