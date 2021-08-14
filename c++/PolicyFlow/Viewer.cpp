
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
	// 40 ���g���؂����ꍇ�̏������l���Ƃ��H
	++ViewerInterface::serialNumber;
}
