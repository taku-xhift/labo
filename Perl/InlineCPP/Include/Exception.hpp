
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

