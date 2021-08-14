
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <cstring>
#include <malloc.h>
#include <cassert>
//#include "../Structure/DBError.h"
#include "Storage.hpp"
#include "ReciprocateData.h"
//#include "../Define/LeagueModeDefineData.h"

//#include "MemoryLeakCheck.hpp"

namespace {
	const char*     playerDataName = "member_data";
	unsigned int    playerDataValueNum = 4;
}



/**----------------------------------------------------
 * @brief �f�[�^�i�[���ς񂾃f�[�^�� error ����t������
 * @note        �`�F�b�N�p�B�{���b������ error �����Ċi�[���邱�Ƃ͂Ȃ��͂��c
 * @param[in]   data_   ��ʂ�̃f�[�^�̊i�[���ς񂾃f�[�^
 * @return      data_ �� error �������f�[�^
 *---------------------------------------------------*/
ReciprocateData* bindDataOnWithError(ReciprocateData* data_, const char* errorWord_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_STRUCT;
	container->key = data_->key;
	container->num = 2;
	container->value = reinterpret_cast<void**>(calloc(2, sizeof(void**)));
	//container->value[0] = reinterpret_cast<void*>(calloc(1, sizeof(DBError)));
	//container->value[0] = reinterpret_cast<void*>(storage_Error(errorWord_, key_DBError), sizeof(ReciprocateData*));
//	container->value[0] = storage_Error(DBErr_NoError, errorWord_);
	container->value[1] = data_;

	return container;
}


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]       data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
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
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_IntArray(const std::vector<int>& data_, const char* key_)
{
	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_INTARRAY;
	container->num = data_.size();
	container->key = key_;

	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(ReciprocateData)));

	for (int i = 0; i < container->num; ++i) {
		container->value[i] = storage_Int(data_[i], key_);
	}

	return container;
}


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]       data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_String(const char* data_, const char* key_)
{
	assert(data_);

	ReciprocateData* container = createReciprocateData();
	container->type = DATATYPE_STRING;
	container->key = key_;
	container->num = 1;
	container->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));
	container->value[0] = reinterpret_cast<void*>(calloc(strlen(data_), strlen(data_) * sizeof(char)));
	memmove(container->value[0], data_, strlen(data_) * sizeof(char));

	return container;
}


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]       data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
//ReciprocateData* storage_Error(const char* data_, const char* key_)
//{
//	assert(data_);
//
//	ReciprocateData* container = createReciprocateData();
//	container->type = DATATYPE_STRING;
//	container->key = key_;
//	container->num = 1;
//	container->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));
//	container->value[0] = reinterpret_cast<void*>(calloc(strlen(data_), strlen(data_) * sizeof(char)));
//	memmove(container->value[0], data_, strlen(data_) * sizeof(char));
//
//	return container;
//}




