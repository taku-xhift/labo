/**
 * @file  Specialize.cpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.01.23 21:39:54
 *
 * @version 1.00, Shishido Takuya, 2012.01.23 21:39:54
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


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



