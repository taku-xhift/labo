/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.06 14:07:58
 *
 * @version 0.01, Shishido Takuya, 2010.04.06 14:07:58
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"

/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @note       ちょっと挙動が怪しいかも TODO
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  dataSet_         出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const ReciprocateData& reciprocateData_)
{
	os << "DataType : " << reciprocateData_.type << std::endl;
	os << "num : " << reciprocateData_.num << std::endl;
	os << "data : " << std::endl;

	switch (reciprocateData_.type) {
		case DATATYPE_INT: {
			int** array = reinterpret_cast<int**>(reciprocateData_.value);
			for (int i = 0; i < reciprocateData_.num; ++i) {
				os << "data[" << i << "] = " << *array[i] << "\n" << std::endl;
			}
			break;
		}
		case DATATYPE_FLOAT: {
			float** array = reinterpret_cast<float**>(reciprocateData_.value);
			for (int i = 0; i < reciprocateData_.num; ++i) {
				os << "data[" << i << "] = " << *array[i] << "\n" << std::endl;
			}
			break;
		}
		case DATATYPE_STRUCT: {
			PlayerData** array = reinterpret_cast<PlayerData**>(reciprocateData_.value);
			for (int i = 0; i < reciprocateData_.num; ++i) {
				os << "data[" << i << "] = " << *array[i] << "\n" << std::endl;
			}
			break;
		}
		case DATATYPE_INVALID:
			// through down
		default: {
			assert(false);
			break;
		}
	}

	return os;
}




