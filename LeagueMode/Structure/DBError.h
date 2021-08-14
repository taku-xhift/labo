
#ifndef DBERROR_H_INCLUDED
#define DBERROR_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------


typedef enum {
	DB_ERRORTYPE_NOERROR,           //!< �G���[�Ȃ�
	DB_ERRORTYPE_NOTFOUND,          //!< �T���ɂ�������������Ȃ������ꍇ
	DB_ERRORTYPE_COMMANDERROR,      //!< �R�}���h���s���Ȃ��̂�����
	DB_ERRORTYPE_DBERROR,           //!< DB �̕��ŉ����G���[���������炵��
	DB_ERRORTYPE_INVALIDDATA,       //!< DB �ɓn�����f�[�^���s���ȃf�[�^������
	DB_ERRORTYPE_MAX,
} DB_ErrorType;



/**
 * @brief DB ����̃G���[�����܂񂾂���
 *          
 * @author  Takuya Shishido
 * @date    2010.04.22 12:52:03
 * @version 0.01, Shishido Takuya, 2010.04.22 12:52:03
 */
typedef struct
{
	char error[0xff];
} DBError;



/**----------------------------------------------------
 * @brief ErrorType �� const char* �ɕϊ�
 * @param[in]   error_      �G���[�̓��e
 * @return      �Ή�����������
 *---------------------------------------------------*/
//const char* convertFromErrorTypeToChar(DB_ErrorType error_);


#endif

