/**
 * @file  weDebug.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.06.01 15:29:01
 *
 * @version 0.01, Shishido Takuya, 2011.06.01 15:29:01
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

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

