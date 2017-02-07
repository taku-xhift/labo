/**
 * @file  Specialize.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.01.23 21:39:54
 *
 * @version 1.00, Shishido Takuya, 2012.01.23 21:39:54
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef SPECIALIZE_HPP_INCLUDED
#define SPECIALIZE_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------


enum SomeDefine {
	HogeHuga,
	HugaHuga,
};

template<SomeDefine def, unsigned int N>
int function() {
	return N;
}
template<>
int function<HogeHuga, HugaHuga>();


class Specialize
{
public:

	/****************************************************************
	 * @brief constructor
	 ***************************************************************/
	Specialize() throw();


	/****************************************************************
	 * @brief destructor
	 ***************************************************************/
	~Specialize() throw();

	template<int i>
	int get() throw();

private:



};    // class Specialize


#endif

