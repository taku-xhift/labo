
#ifndef GAMERESULT_H_INCLUDED
#define GAMERESULT_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <time.h>

typedef enum
{
	GAMERESULTCATEGORY_WIN,
	GAMERESULTCATEGORY_LOSE,
	GAMERESULTCATEGORY_PKWIN,
	GAMERESULTCATEGORY_PKLOSE,
	GAMERESULTCATEGORY_INVALID,
	GAMERESULTCATEGORY_MAX,
} GameResultCategory;

/**
 * @brief �������ʂ�ۑ����Ă����\����
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 15:06:36
 * @version 0.01, Shishido Takuya, 2010.04.07 15:06:36
 */
typedef struct
{
	char    name[0xff];     //!< ���O
	time_t  time;           //!< �����J�n���ԁB�ΐ푊��͂���Ō�������
	int     score;          //!< �����̃X�R�A�i�����́j
	int     victory;        //!< �������� 1 �A�������� 0 �A�ؒf�Ȃǖ����Ȃ� -1
} GameResult;    // struct GameResult

#endif

