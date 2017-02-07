/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.16 15:10:07
 *
 * @version 0.01, Shishido Takuya, 2010.04.16 15:10:07
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef CONVERTER_HPP_INCLUDED
#define CONVERTER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/DBError.h"


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
DBError convertToDBError(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
PlayerData convertToPlayerData(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
TeamData convertToTeamData(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());


#endif

