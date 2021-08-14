
#ifndef ASSERT_HPP_INCLUDED
#define ASSERT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <cstdio>
#include "stdlib.h"


/**----------------------------------------------------
 * @brief user's assertion
 * @note    �ʏ�N���ł͕��ʂ� assert() �Ƃ��ē���B
 *              NDEBUG �ŋN�����Ă��G���[���O�����͎擾�ł���B
 *              �A���Aabort() �͓��삵�Ȃ��B
 * @param[in]   expression_     ���肷��f�[�^
 * @param[in]   message_        �\�����郁�b�Z�[�W
 *---------------------------------------------------*/
#ifdef NDEBUG
#define userAssert(expression_, message_) {\
	if(expression_){\
		printf("assert: %s \n%s\n%s��%d�s��\n", #expression_, message_, __FILE__, __LINE__);\
	}\
}
#else
#define userAssert(expression_, message_) {\
	if(expression_){\
		printf("assert: %s \n%s\n%s��%d�s��\n", #expression_, message_, __FILE__, __LINE__);\
		abort();\
	}\
}
#endif



#endif

