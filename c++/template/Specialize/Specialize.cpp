
//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "Specialize.hpp"


template<>
int function<HogeHuga, HugaHuga>() {
	return 100;
}


/********************************************************************
 * @brief constructor
 *******************************************************************/
Specialize::Specialize() throw()
{

}



/********************************************************************
 * @brief destructor
 *******************************************************************/
Specialize::~Specialize() throw()
{

}



template<int i>
int Specialize::get() throw() {
	return i;
}
template<>
int Specialize::get<1>() throw() {
	return 1;
}



