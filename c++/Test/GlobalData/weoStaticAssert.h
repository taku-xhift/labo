/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.05 08:46:26
 *
 * @version 0.01, Shishido Takuya, 2011.04.05 08:46:26
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef STATICASSERT_HPP_INCLUDED
#define STATICASSERT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#define STATIC_ASSERT(cond)             extern int assert_function(int [(cond)?1:-1])


#endif

