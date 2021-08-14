
#ifndef PLAYERDATA_H_INCLUDED
#define PLAYERDATA_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "ReciprocateData.h"

//-----------------------------------------------------
//  declaration
//-----------------------------------------------------



/**
 * @brief �I��f�[�^�܂Ƃ�
 * @note    cpp �Ŏg���ۂɂ� PlayerDataForCpp ���g�����������߁B�o�͂��T�|�[�g���Ă��炦��B
 * @author  Takuya Shishido
 * @date    2010.04.02 15:09:22
 * @version 0.01, Shishido Takuya, 2010.04.02 15:09:22
 */
typedef struct
{
	char        name[0xff];     //!< �I�薼
	int         entryNumber;    //!< �w�ԍ�
	int         offence;        //!< �I�t�F���X
	int         defence;        //!< �f�B�t�F���X
} PlayerData;    // struct PlayerData



#endif

