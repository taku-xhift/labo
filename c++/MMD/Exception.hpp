/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.07.12 16:49:58
 *
 * @version 1.00, Shishido Takuya, 2012.07.12 16:49:58
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef MMD_EXCEPTION_HPP_INCLUDED
#define MMD_EXCEPTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <exception>


namespace mmd {


struct ExceptionBase
	: public std::exception
{
	virtual const char* what() throw() { return "Exception"; }
};


struct UnFoundFileException
	: public ExceptionBase
{
	virtual const char* what() throw() { return "UnFoundFileException"; }
};

}    // namespace mmd


#endif

