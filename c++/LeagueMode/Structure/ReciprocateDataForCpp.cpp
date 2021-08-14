
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "ReciprocateDataForCpp.hpp"
#include "PlayerDataForCpp.hpp"
#include "MemoryLeakCheck.hpp"

/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @note       ������Ƌ��������������� TODO
 * @param[in]  os               �X�g���[���I�u�W�F�N�g
 * @param[in]  dataSet_         �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const ReciprocateData& reciprocateData_)
{
	os << "DataType : " << reciprocateData_.type << std::endl;
	os << "num : " << reciprocateData_.num << std::endl;
	os << "data : " << std::endl;

	switch (reciprocateData_.type) {
		case DATATYPE_INT: {
			int** array = reinterpret_cast<int**>(reciprocateData_.data);
			for (int i = 0; i < reciprocateData_.num; ++i) {
				os << "data[" << i << "] = " << *array[i] << "\n" << std::endl;
			}
			break;
		}
		case DATATYPE_FLOAT: {
			float** array = reinterpret_cast<float**>(reciprocateData_.data);
			for (int i = 0; i < reciprocateData_.num; ++i) {
				os << "data[" << i << "] = " << *array[i] << "\n" << std::endl;
			}
			break;
		}
		case DATATYPE_PLAYERDATA: {
			PlayerData** array = reinterpret_cast<PlayerData**>(reciprocateData_.data);
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




