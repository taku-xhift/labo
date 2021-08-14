
#ifndef GAMERESULTFORCPP_HPP_INCLUDED
#define GAMERESULTFORCPP_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "GameResult.h"

/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @note       ちょっと挙動が怪しいかも TODO
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  dataSet_         出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const GameResult& gameResult_);



#endif

