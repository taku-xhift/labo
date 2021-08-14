
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

