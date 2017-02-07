/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.13 16:00:17
 *
 * @version 0.01, Shishido Takuya, 2010.04.13 16:00:17
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <assert.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"


#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"

/**----------------------------------------------------
 * @brief 例外文字列の取得
 * @return  文字列の先頭ポインタ
 *---------------------------------------------------*/
const char* ParseException::what() const throw()
{
	return "ParseException";
}


/**----------------------------------------------------
 * @brief Perl 側から受け取ったデータを解析する
 * @param[in]       reciprocateData_    Perl から受け取ったデータ
 * @return          reciprocateData_->type 型のデータを void* に変換したもの
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key_, std::vector<int> node_ /* = std::vector<int>()*/) throw(ParseException)
{
	if (reciprocateData_.type == DATATYPE_INT
		|| reciprocateData_.type == DATATYPE_FLOAT
		|| reciprocateData_.type == DATATYPE_STRING)
	{
		if (strcmp(reciprocateData_.key, key_) != 0) {
			// 末端でのキー判定で見つからなかった
			return NULL;
		}
		return reciprocateData_.value[0];
	}

	else if (reciprocateData_.type == DATATYPE_INTARRAY
		|| reciprocateData_.type == DATATYPE_FLOATARRAY)
	{
		// キーが一致すればすぐさま返す
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// ノードがカラッポ
			assert(0);
		}
		if (reciprocateData_.num+1 < node_.front()) {
			// ノード値が異常です
			assert(0);
		}

		if (strcmp(reciprocateData_.key, key_) != 0) {
			// 末端でのキー判定で見つからなかった
			return NULL;
		}
		return reciprocateData_.value[node_.front()];
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
		throw ParseException();
	}

	else if (reciprocateData_.type == DATATYPE_STRUCTARRAY) {
		// キーが一致すればすぐさま返す
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// ノードがカラッポ
			assert(0);
		}
		int accessNode = node_.front();
		if (reciprocateData_.num-1 < accessNode) {
			// ノード値が異常
			assert(0);
		}
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[accessNode]);
		return getKeyValue(*value, key_, node_);
	}

	else {
		// 異常な型情報が入っている
		assert(0);
		return NULL;
	}
}



