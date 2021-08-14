
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <cstring>
#include <assert.h>
#include "Parse.hpp"
//#include "UtilityFunction.hpp"


//#include "MemoryLeakCheck.hpp"


/**----------------------------------------------------
 * @brief Perl ������󂯎�����f�[�^����͂���
 * @param[in]       reciprocateData_    Perl ����󂯎�����f�[�^
 * @return          reciprocateData_->type �^�̃f�[�^�� void* �ɕϊ���������
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key_, std::vector<int> node_ /* = std::vector<int>()*/)
{
	if (reciprocateData_.type == DATATYPE_INT
		|| reciprocateData_.type == DATATYPE_FLOAT
		|| reciprocateData_.type == DATATYPE_STRING)
	{
		if (strcmp(reciprocateData_.key, key_) != 0) {
			// ���[�ł̃L�[����Ō�����Ȃ�����
			// �����͍\���̂�z��̃`�F�b�N�̏ꍇ�ɕp�ɂɒʂ�̂� assert �͎d�|���Ȃ�
			return NULL;
		}
		return reciprocateData_.value[0];
	}

	else if (reciprocateData_.type == DATATYPE_INTARRAY
		|| reciprocateData_.type == DATATYPE_FLOATARRAY)
	{
		if (node_.empty()) {
			// �m�[�h�l����ŃL�[����v����΂������ܕԂ�
			if (strcmp(reciprocateData_.key, key_) == 0) {
				return reinterpret_cast<const void*>(&reciprocateData_);
			}

			// �m�[�h���J���b�|
//			userAssert(0, "node_ is empty!!");
			return NULL;
		}
		if (reciprocateData_.num <= node_.at(node_.size()-1)) {
			// �m�[�h�l���ُ�ł�
//			userAssert(0, "node_ is invalid!!");
			return NULL;
		}

		if (strcmp(reciprocateData_.key, key_) != 0) {
			// ���[�ł̃L�[����Ō�����Ȃ�����
//			userAssert(0, "The key is not found!!");
			return NULL;
		}
		//return reciprocateData_.value[node_.at(node_.size()-1)];
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[node_.at(node_.size()-1)]);
		node_.pop_back();    // ����� node �͏������Ă���
		const void* result = getKeyValue(*value, key_, node_);
		return result;
	}

	else if (reciprocateData_.type == DATATYPE_STRUCT) {
		// �L�[����v����΂������ܕԂ�
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

		// �����ɂ��ǂ蒅�������_�Ō������ĂȂ�
//		userAssert(0, "The key is not found!!");
		return NULL;
	}

	else if (reciprocateData_.type == DATATYPE_STRUCTARRAY) {
		// �L�[����v����΂������ܕԂ�
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// �m�[�h���J���b�|
//			userAssert(0, "node_ is empty!!");
			return NULL;
		}
		int accessNode = node_.at(node_.size()-1);
		if (reciprocateData_.num-1 < accessNode) {
			// �m�[�h�l���ُ�
//			userAssert(0, "node_ is invalid!!");
			return NULL;
		}
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[accessNode]);
		node_.pop_back();    // ����� node ���������Ă���
		return getKeyValue(*value, key_, node_);
	}

	else {
		// �ُ�Ȍ^��񂪓����Ă���
//		userAssert(0, "The type is invalid");
		return NULL;
	}
}



