
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <assert.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"


#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"

/**----------------------------------------------------
 * @brief ��O������̎擾
 * @return  ������̐擪�|�C���^
 *---------------------------------------------------*/
const char* ParseException::what() const throw()
{
	return "ParseException";
}


/**----------------------------------------------------
 * @brief Perl ������󂯎�����f�[�^����͂���
 * @param[in]       reciprocateData_    Perl ����󂯎�����f�[�^
 * @return          reciprocateData_->type �^�̃f�[�^�� void* �ɕϊ���������
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key_, std::vector<int> node_ /* = std::vector<int>()*/) throw(ParseException)
{
	if (reciprocateData_.type == DATATYPE_INT
		|| reciprocateData_.type == DATATYPE_FLOAT
		|| reciprocateData_.type == DATATYPE_STRING)
	{
		if (strcmp(reciprocateData_.key, key_) != 0) {
			// ���[�ł̃L�[����Ō�����Ȃ�����
			return NULL;
		}
		return reciprocateData_.value[0];
	}

	else if (reciprocateData_.type == DATATYPE_INTARRAY
		|| reciprocateData_.type == DATATYPE_FLOATARRAY)
	{
		// �L�[����v����΂������ܕԂ�
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// �m�[�h���J���b�|
			assert(0);
		}
		if (reciprocateData_.num+1 < node_.front()) {
			// �m�[�h�l���ُ�ł�
			assert(0);
		}

		if (strcmp(reciprocateData_.key, key_) != 0) {
			// ���[�ł̃L�[����Ō�����Ȃ�����
			return NULL;
		}
		return reciprocateData_.value[node_.front()];
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
		throw ParseException();
	}

	else if (reciprocateData_.type == DATATYPE_STRUCTARRAY) {
		// �L�[����v����΂������ܕԂ�
		if (strcmp(reciprocateData_.key, key_) == 0) {
			return reinterpret_cast<const void*>(&reciprocateData_);
		}

		if (node_.empty()) {
			// �m�[�h���J���b�|
			assert(0);
		}
		int accessNode = node_.front();
		if (reciprocateData_.num-1 < accessNode) {
			// �m�[�h�l���ُ�
			assert(0);
		}
		ReciprocateData* value = reinterpret_cast<ReciprocateData*>(reciprocateData_.value[accessNode]);
		return getKeyValue(*value, key_, node_);
	}

	else {
		// �ُ�Ȍ^��񂪓����Ă���
		assert(0);
		return NULL;
	}
}



