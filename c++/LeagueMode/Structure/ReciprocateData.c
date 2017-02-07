/**
 * @file
 * @brief データベースへのアクセスをイメージした関数群
 *
 * @author Takuya Shishido
 * @date 2010.04.02 15:56:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 15:56:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


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
 * @brief dataSet 型の解放関数
 * @note    address、data に関しては free をする。
 *              type は DATATYPE_INVALID にて初期化。
 *              num は INT_MAX にて初期化を行います。
 * @param[out]  dataSet_    データを解放したいもの
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
		// ↓ through down 
		default: {
			// 不正なデータ型になっている
			assert(0);
			break;
		}
	}
}



