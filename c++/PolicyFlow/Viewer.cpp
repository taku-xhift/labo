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
#include <memory>
#include <typeinfo>
#include <limits>


unsigned int ViewerInterface::serialNumber = 0;

ViewerInterface::ViewerInterface(int parentID_ /*= std::numeric_limits<unsigned int>::max()*/)
	: uniqueID(ViewerInterface::serialNumber)
	, parentID(parentID)
{
	// 40 ‰­g‚¢Ø‚Á‚½ê‡‚Ìˆ—‚ğl‚¦‚Æ‚­H
	++ViewerInterface::serialNumber;
}
