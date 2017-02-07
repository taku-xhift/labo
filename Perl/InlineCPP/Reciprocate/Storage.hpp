/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.14 11:09:31
 *
 * @version 0.01, Shishido Takuya, 2010.04.14 11:09:31
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef STORAGE_HPP_INCLUDED
#define STORAGE_HPP_INCLUDED

//-----------------------------------------------------
//  includ
//-----------------------------------------------------
#include <iostream>
#include <vector>
#include <malloc.h>
#include "ReciprocateData.h"



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_Int(int data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_INT;
	container->key = key_;
	container->num = 1;
	container->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));
	container->value[0] = reinterpret_cast<void*>(calloc(1, sizeof(int)));
	memmove(container->value[0], &data_, sizeof(int));

	return container;
}



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_IntArray(const std::vector<int>& data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_INTARRAY;
	container->num = data_.size();
	container->key = key_;

	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(ReciprocateData)));

	for (int i = 0; i < container->num; ++i) {
		container->value[i] = storage_Int(data_.at(i), key_);
	}

	return container;
}



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_Float(float data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_FLOAT;
	container->key = key_;
	container->num = 1;
	container->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));
	container->value[0] = reinterpret_cast<void*>(calloc(1, sizeof(float)));
	memmove(container->value[0], &data_, sizeof(float));

	return container;
}



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_FloatArray(const std::vector<float>& data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_FLOATARRAY;
	container->num = data_.size();
	container->key = key_;

	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(ReciprocateData)));

	for (int i = 0; i < container->num; ++i) {
		container->value[i] = storage_Float(data_.at(i), key_);
	}

	return container;
}



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_String(const char* data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_STRING;
	container->key = key_;
	container->num = 1;
	container->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));
	container->value[0] = reinterpret_cast<void*>(calloc(strlen(data_), strlen(data_) * sizeof(char)));
	memmove(container->value[0], data_, strlen(data_) * sizeof(char));

	return container;
}


struct PlayerData {
    int number;
    const char* name;
};


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_PlayerData(const PlayerData& data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_STRUCT;
	container->key = key_;
	container->num = 2;
	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(void**)));
	container->value[0] = storage_Int(data_.number, "number");
	container->value[1] = storage_String(data_.name, "name");

	return container;
}



#endif

