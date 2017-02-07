/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.13 16:00:17
 *
 * @version 0.01, Shishido Takuya, 2010.04.13 16:00:17
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <cstring>
#include <assert.h>
#include "ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

void userAssert(bool boolean_, const char* strings_) {
	std::cout << strings_ << std::endl;
	assert(boolean_);
}


/**----------------------------------------------------
 * @brief Perl 側から受け取ったデータを解析する
 * @param[in]       reciprocateData_    Perl から受け取ったデータ
 * @return          reciprocateData_->type 型のデータを void* に変換したもの
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key_, std::vector<int> node_  = std::vector<int>())
{
	//std::cout << "reciprocateData_.key = " << reciprocateData_.key << std::endl;
	//std::cout << "reciprocateData_.type = " << reciprocateData_.type << std::endl;
	//std::cout << "node_.size() = " << node_.size() << std::endl;

	if (reciprocateData_.type == DATATYPE_INT
		|| reciprocateData_.type == DATATYPE_FLOAT
		|| reciprocateData_.type == DATATYPE_STRING)
	{
		if (strcmp(reciprocateData_.key, key_) != 0) {
			// 末端でのキー判定で見つからなかった
			// ここは構造体や配列のチェックの場合に頻繁に通るので assert は仕掛けない
			return NULL;
		}
		return reciprocateData_.value[0];
	}

	else if (reciprocateData_.type == DATATYPE_INTARRAY
		|| reciprocateData_.type == DATATYPE_FLOATARRAY)
	{
		if (node_.empty()) {
			// ノード値が空でキーが一致すればすぐさま返す
			if (strcmp(reciprocateData_.key, key_) == 0) {
				return reinterpret_cast<const void*>(&reciprocateData_);
			}

			// ノードがカラッポ
			userAssert(0, "node_ is empty!!");
			return NULL;
		}
		if (reciprocateData_.num < node_.at(node_.size()-1)) {
			// ノード値が異常です
			userAssert(0, "node_ is invalid!!");
			return NULL;
		}

//		if (strcmp(reciprocateData_.key, key_) != 0) {
//			// 末端でのキー判定で見つからなかった
//			std::cout << "key = " << key_ << std::endl;
//			std::cout << "type = " << reciprocateData_.type << std::endl;
//			userAssert(0, "The key is not found!!");
//			return NULL;
//		}
		//return reciprocateData_.value[node_.at(node_.size()-1)];
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[node_.at(node_.size()-1)]);
		node_.pop_back();    // 消費した node は消去しておく
		const void* result = getKeyValue(*value, key_, node_);
		return result;
	}

	else if (reciprocateData_.type == DATATYPE_STRUCT) {
		// キーが一致すればすぐさま返す
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		ReciprocateData* value;
		for (int i = 0; i < reciprocateData_.num; ++i) {
			value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[i]);
			const void* result = getKeyValue(*value, key_, node_);
			if (result) {
				return result;
			}
		}

		// ここにたどり着いた時点で見つけられてない
		//std::cout << "key = " << key_ << std::endl;
		//std::cout << "type = " << reciprocateData_.type << std::endl;
		//userAssert(0, "The key is not found!!");
		return NULL;
	}

	else if (reciprocateData_.type == DATATYPE_STRUCTARRAY) {
		// キーが一致すればすぐさま返す
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// ノードがカラッポ
			userAssert(0, "node_ is empty!!");
			return NULL;
		}
		int accessNode = node_.at(node_.size()-1);
		if (reciprocateData_.num < accessNode) {
			// ノード値が異常
			userAssert(0, "node_ is invalid!!");
			return NULL;
		}
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[accessNode]);
		node_.pop_back();    // 消費した node を消去しておく
		return getKeyValue(*value, key_, node_);
	}

	else {
		// 異常な型情報が入っている
		userAssert(0, "The type is invalid");
		return NULL;
	}
}


#ifdef __cplusplus
}
#endif

#endif

