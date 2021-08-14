
#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

/**----------------------------------------------------
 * @brief Perl ������󂯎�����f�[�^����͂���
 * @param[in]       reciprocateData_    Perl ����󂯎�����f�[�^
 * @return          reciprocateData_->type �^�̃f�[�^�� void* �ɕϊ���������
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key, std::vector<int> node_ = std::vector<int>());


#ifdef __cplusplus
}
#endif

#endif

