/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.06.08 15:07:35
 *
 * @version 0.01, Shishido Takuya, 2010.06.08 15:07:35
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef EXCEPTION_HPP_INCLUDED
#define EXCEPTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <Exception>


/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
const char* checkStrings(const char* strings, bool canThrow_) throw(std::exception);

#endif

