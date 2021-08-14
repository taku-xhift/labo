
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

