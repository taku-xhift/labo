/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.06.09 15:55:18
 *
 * @version 0.01, Shishido Takuya, 2010.06.09 15:55:18
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef ASSERT_HPP_INCLUDED
#define ASSERT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <cstdio>
#include "stdlib.h"


/**----------------------------------------------------
 * @brief user's assertion
 * @note    通常起動では普通の assert() として動作。
 *              NDEBUG で起動してもエラーログだけは取得できる。
 *              但し、abort() は動作しない。
 * @param[in]   expression_     判定するデータ
 * @param[in]   message_        表示するメッセージ
 *---------------------------------------------------*/
#ifdef NDEBUG
#define userAssert(expression_, message_) {\
	if(expression_){\
		printf("assert: %s \n%s\n%sの%d行目\n", #expression_, message_, __FILE__, __LINE__);\
	}\
}
#else
#define userAssert(expression_, message_) {\
	if(expression_){\
		printf("assert: %s \n%s\n%sの%d行目\n", #expression_, message_, __FILE__, __LINE__);\
		abort();\
	}\
}
#endif



#endif

