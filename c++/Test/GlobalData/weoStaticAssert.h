
#ifndef STATICASSERT_HPP_INCLUDED
#define STATICASSERT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#define STATIC_ASSERT(cond)             extern int assert_function(int [(cond)?1:-1])


#endif

