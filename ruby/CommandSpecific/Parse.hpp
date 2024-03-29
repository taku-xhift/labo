
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
 * @brief Perl 側から受け取ったデータを解析する
 * @param[in]       reciprocateData_    Perl から受け取ったデータ
 * @return          reciprocateData_->type 型のデータを void* に変換したもの
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key, std::vector<int> node_ = std::vector<int>());


#ifdef __cplusplus
}
#endif

#endif

