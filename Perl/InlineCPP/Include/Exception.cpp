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


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Exception.hpp"


/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
const char* checkStrings(const char* strings, bool canThrow_) throw(std::exception)
{
	if (canThrow_) {
		throw std::exception();
	} else {
		return strings;
	}
}


