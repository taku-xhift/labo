
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
	int     adversaryID;    //!< �ΐ푊��̃��[�U�h�c
	time_t  time;           //!< �����J�n����
	int     teamID;         //!< �g�p�����`�[���̂h�c
	int     victory;        //!< �������� 1 �A�������� 0 �A�ؒf�Ȃǖ����Ȃ� -1
	int     goal;           //!< ���_
	int     loss;           //!< ���_

} GameResult;    // struct GameResult

#endif

