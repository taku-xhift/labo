
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <malloc.h>
#include <assert.h>
#include <limits.h>
#include "Reciprocate.h"
#include "PlayerData.h"



//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
void releaseAddress(ReciprocateData* reciprocateData_);



/**----------------------------------------------------
 * @brief dataSet �^�̉���֐�
 * @note    address�Adata �Ɋւ��Ă� free ������B
 *              type �� DATATYPE_INVALID �ɂď������B
 *              num �� INT_MAX �ɂď��������s���܂��B
 * @param[out]  dataSet_    �f�[�^���������������
 *---------------------------------------------------*/
void releaseReciprocateData(ReciprocateData* reciprocateData_)
{
	releaseAddress(reciprocateData_);
	free(reciprocateData_->data);
	reciprocateData_->type = DATATYPE_INVALID;
	reciprocateData_->num = INT_MAX;
}



//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
void releaseAddress(ReciprocateData* reciprocateData_)
{
	switch (reciprocateData_->type) {
		case DATATYPE_INT: {
			free((int*)reciprocateData_->address);
			break;
		}
		case DATATYPE_FLOAT: {
			free((float*)reciprocateData_->address);
			break;
		}
		case DATATYPE_PLAYERDATA: {
			free((PlayerData*)reciprocateData_->address);
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



