
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

