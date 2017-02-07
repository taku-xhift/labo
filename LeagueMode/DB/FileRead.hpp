/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 18:41:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 18:41:12
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef FILEREAD_HPP_INCLUDED
#define FILEREAD_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"

#ifdef __cplusplus
extern "C" {
#endif



/**----------------------------------------------------
 * @brief ファイルからチームの名前を頼りに選手データを読み込む
 * @note    これは本来 Perl で行われるべき処理のはずだが、
 *              先行して cpp にて作成。
 *              perl が追いついたらそちらに置換されるべき。
 * @param[in]   teamName_           探すチーム名
 * @param[out]  reciprocateData_    データ格納を行う場所。
 *                                      これは C と perl のデータのやり取りを行うためのデータ。
 *---------------------------------------------------*/
void readFile_TeamDataInformation(const char* teamName_, ReciprocateData* reciprocateData_);

#ifdef __cplusplus
}
#endif


#endif

