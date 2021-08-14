
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
	// 40 ���g���؂����ꍇ�̏������l���Ƃ��H
	++ModelerInterface::serialNumber;
}


