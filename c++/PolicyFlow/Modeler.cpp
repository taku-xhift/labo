/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.10.07 15:20:08
 *
 * @version 0.01, Shishido Takuya, 2010.10.07 15:20:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <typeinfo>

#include "Modeler.hpp"
#include "Utility.hpp"

unsigned int ModelerInterface::serialNumber = 0;

ModelerInterface::ModelerInterface(unsigned int parentID_ /*= std::numeric_limits<unsigned int>::max()*/)
	: uniqueID(ModelerInterface::serialNumber)
	, parentID(parentID)
{
	// 40 ‰­g‚¢Ø‚Á‚½ê‡‚Ìˆ—‚ğl‚¦‚Æ‚­H
	++ModelerInterface::serialNumber;
}


