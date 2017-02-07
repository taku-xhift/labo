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
#include "ReciprocateData.h"
//#include "PlayerData.h"



//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
void releaseValue(ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief ReciprocateData 型のメモリ取得関数
 * @note    中身は calloc() しているだけ。
 *              releaseReciprocateData() とのセットにしている
 * @return  確保されたメモリのアドレス
 *---------------------------------------------------*/
ReciprocateData* createReciprocateData()
{
	return (ReciprocateData*)(calloc(1, sizeof(ReciprocateData)));
}



/**----------------------------------------------------
 * @brief dataSet 型の解放関数
 * @note    address、data に関しては free をする。
 *              type は DATATYPE_INVALID にて初期化。
 *              num は INT_MAX にて初期化を行います。
 * @param[out]  dataSet_    データを解放したいもの
 *---------------------------------------------------*/
void releaseReciprocateData(ReciprocateData* reciprocateData_)
{
	releaseValue(reciprocateData_);
	free(reciprocateData_);
}



/**----------------------------------------------------
 * @brief ReciprocateData 型の解放関数
 * @note    value に関しては free をする。
 *              type は DATATYPE_INVALID にて初期化。
 *              num は INT_MAX にて初期化を行います。
 * @param[out]  reciprocateData_    データを解放したいもの
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
		// ↓ through down 
		default: {
			// 不正なデータ型になっている
			assert(0);
			break;
		}
	}
}


