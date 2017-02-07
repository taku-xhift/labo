/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 18:41:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 18:41:12
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef FILEREAD_HPP_INCLUDED
#define FILEREAD_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "../ReciprocateData.h"

#ifdef __cplusplus
extern "C" {
#endif



void readFile_TeamInformation(const char* teamName_, ReciprocateData* reciprocateData_);

#ifdef __cplusplus
}
#endif


#endif

