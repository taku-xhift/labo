
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <malloc.h>
#include <assert.h>
#include <limits.h>
#include "ReciprocateData.h"
//#include "PlayerData.h"



//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
void releaseValue(ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief ReciprocateData �^�̃������擾�֐�
 * @note    ���g�� calloc() ���Ă��邾���B
 *              releaseReciprocateData() �Ƃ̃Z�b�g�ɂ��Ă���
 * @return  �m�ۂ��ꂽ�������̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* createReciprocateData()
{
	return (ReciprocateData*)(calloc(1, sizeof(ReciprocateData)));
}



/**----------------------------------------------------
 * @brief dataSet �^�̉���֐�
 * @note    address�Adata �Ɋւ��Ă� free ������B
 *              type �� DATATYPE_INVALID �ɂď������B
 *              num �� INT_MAX �ɂď��������s���܂��B
 * @param[out]  dataSet_    �f�[�^���������������
 *---------------------------------------------------*/
void releaseReciprocateData(ReciprocateData* reciprocateData_)
{
	releaseValue(reciprocateData_);
	free(reciprocateData_);
}



/**----------------------------------------------------
 * @brief ReciprocateData �^�̉���֐�
 * @note    value �Ɋւ��Ă� free ������B
 *              type �� DATATYPE_INVALID �ɂď������B
 *              num �� INT_MAX �ɂď��������s���܂��B
 * @param[out]  reciprocateData_    �f�[�^���������������
 *---------------------------------------------------*/
void releaseValue(ReciprocateData* reciprocateData_)
{
	int i = 0;

	switch (reciprocateData_->type) {
		case DATATYPE_STRING: {
			free((char*)reciprocateData_->value[0]);
			free(reciprocateData_->value);
			break;
		}
		case DATATYPE_INT: {
			free((int*)reciprocateData_->value[0]);
			free(reciprocateData_->value);
			break;
		}
		case DATATYPE_INTARRAY: {
			for (i = 0; i < reciprocateData_->num; ++i) {
				releaseValue((ReciprocateData*)reciprocateData_->value[i]);
				free((ReciprocateData*)reciprocateData_->value[i]);
			}
			free((ReciprocateData*)reciprocateData_->value);
			break;
		}
		case DATATYPE_FLOAT: {
			free((float*)reciprocateData_->value[0]);
			break;
		}
		case DATATYPE_FLOATARRAY: {
			for (i = 0; i < reciprocateData_->num; ++i) {
				releaseValue((ReciprocateData*)reciprocateData_->value[i]);
				free((ReciprocateData*)reciprocateData_->value[i]);
			}
			free((ReciprocateData*)reciprocateData_->value);
			break;
		}
		case DATATYPE_STRUCT: {
			for (i = 0; i < reciprocateData_->num; ++i) {
				releaseValue((ReciprocateData*)reciprocateData_->value[i]);
				free((ReciprocateData*)reciprocateData_->value[i]);
			}
			free((ReciprocateData*)reciprocateData_->value);
			break;
		}
		case DATATYPE_STRUCTARRAY: {
			for (i = 0; i < reciprocateData_->num; ++i) {
				releaseValue((ReciprocateData*)reciprocateData_->value[i]);
				free((ReciprocateData*)reciprocateData_->value[i]);
			}
			free((ReciprocateData*)reciprocateData_->value);
			break;
		}
		case DATATYPE_INVALID:
		// �� through down 
		default: {
			// �s���ȃf�[�^�^�ɂȂ��Ă���
			assert(0);
			break;
		}
	}
}


