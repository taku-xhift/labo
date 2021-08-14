
#ifndef WEDEBUG_HPP_INCLUDED
#define WEDEBUG_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include <cstdio>
#include <assert.h>


#define WE_PRINTF printf
#define WE_ASSERT assert
#define NEW new
#define SAFE_DELETE(ptr) { if (!ptr) { delete ptr; ptr = NULL; } }
#define STATIC_ASSERT(exp, msg)    extern void static_assert_helper_(char arg[(exp)? 1 : -1])

#endif

