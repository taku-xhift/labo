/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.01.06 23:20:28
 *
 * @version 0.01, Shishido Takuya, 2012.01.06 23:20:28
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <limits>
#include "TestClass.hpp"
#include "UnExportFunction.hpp"


#define _EXPORTING


namespace mode {

//! \brief constructor
TestClass::TestClass() throw()
	: integer_(std::numeric_limits<int>::max())
{
	this->integer_ = add(2, 4);
}


//! \brief destructor
TestClass::~TestClass() throw()
{

}


}    // namespace mode

