/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.06 14:07:58
 *
 * @version 0.01, Shishido Takuya, 2010.04.06 14:07:58
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef RECIPROCATEDATAFORCPP_HPP_INCLUDED
#define RECIPROCATEDATAFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  dataSet_         出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const ReciprocateData& reciprocateData_);


#endif  // RECIPROCATEDATAFORCPP_HPP_INCLUDED

