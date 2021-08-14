
#ifndef DBACCESS_H_INCLUDED
#define DBACCESS_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <assert.h>


typedef enum
{
	DATATYPE_INT,
	DATATYPE_FLOAT,
	DATATYPE_PLAYERDATA,
	DATATYPE_INVALID,
} ReciprocateDataType;



/**
 * @brief perl �� c �Ńf�[�^������肷��ۂ�
 *          �f�[�^�����ɂ������́Bc++ �Ȃ� DBAccessForCpp.hpp �������߁B
 * @note    C++ �Ŏg���ۂɂ� TeamForCpp ���������߁B�o�͂��T�|�[�g���Ă����B

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct
{
	unsigned int    address;            //!< data �����ۂɍ����e���|�����f�[�^�̃A�h���X�B
	                                    //      data ���K�v�Ȃ��Ȃ����ۂɖY�ꂸ�� free �ŊJ�����邱�ƁB
	ReciprocateDataType     type;       //!< �f�[�^�̌^
	int                     num;        //!< �f�[�^���ɓ����Ă���L���f�[�^�̐�
	void**                  data;       //!< �f�[�^�{�́B�z��ɂȂ��Ă���B�v�f���� num �Ŕ��f�Bfree �ŖY�ꂸ�ɊJ�����邱��
} ReciprocateData;



#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief dataSet �^�̉���֐�
 * @note    address�Adata �Ɋւ��Ă� free ������B
 *              type �� DATATYPE_INVALID �ɂď������B
 *              num �� INT_MAX �ɂď��������s���܂��B
 * @param[out]  dataSet_    �f�[�^���������������
 *---------------------------------------------------*/
void releaseReciprocateData(ReciprocateData* reciprocateData_);



#ifdef __cplusplus
}
#endif


#endif

