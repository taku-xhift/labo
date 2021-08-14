
#ifndef DBACCESS_H_INCLUDED
#define DBACCESS_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <assert.h>

#ifdef __cplusplus
#include <iostream>
#endif

typedef enum
{
	DATATYPE_INVALID,
	DATATYPE_STRING,
	DATATYPE_INT,
	DATATYPE_INTARRAY,
	DATATYPE_FLOAT,
	DATATYPE_FLOATARRAY,
	DATATYPE_STRUCT,
	DATATYPE_STRUCTARRAY,
	DATATYPE_MAX,
} ReciprocateDataType;



/**
 * @brief perl �� c �Ńf�[�^������肷��ۂ�
 *          �f�[�^�����ɂ������́Bc++ �Ȃ� DBAccessForCpp.hpp �������߁B
 * @note    C++ �Ŏg���ۂɂ� ForCpp ���������߁B�o�͂��T�|�[�g���Ă����B
 *              �������Anew �͋֎~�B
 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct
{
	ReciprocateDataType     type;       //!< �f�[�^�̌^
	int                     num;        //!< �����̗v�f���BDATATYPE_INT�Ȃ�1�������Ă���B
	                                    //       �\���̂Ȃ烁���o�̐��A�z��Ȃ炻�̗v�f���������Ă���B
	const char*             key;        //!< �f�[�^�̓��e�������L�[
	void**                  value;      //!< �f�[�^�{�́B�z��ɂȂ��Ă���B�v�f���� num �Ŕ��f�Bfree �ŖY�ꂸ�ɊJ�����邱��

	// C++ �p�� new �̋֎~
	// �������A malloc �͋֎~�ł��Ȃ�
	// createReciprocateData() �������� malloc �Ȃ̂Łc
#ifdef __cplusplus
	void* operator new(std::size_t size);
#endif

} ReciprocateData;



#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief ReciprocateData �^�̃������擾�֐�
 * @note    ���g�� calloc() ���Ă��邾���B
 *              releaseReciprocateData() �Ƃ̃Z�b�g�ɂ��Ă���
 * @return  �m�ۂ��ꂽ�������̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* createReciprocateData();


/**----------------------------------------------------
 * @brief ReciprocateData �^�̉���֐�
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
