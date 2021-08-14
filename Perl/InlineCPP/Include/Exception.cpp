
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


