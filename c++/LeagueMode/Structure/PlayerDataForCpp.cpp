/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.06 13:59:00
 *
 * @version 0.01, Shishido Takuya, 2010.04.06 13:59:00
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "PlayerDataForCpp.hpp"



/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os               ストリームオブジェクト
 * @param[in]  playerData_      出力オブジェクト
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const PlayerData& playerData_)
{
	os << "name : " << playerData_.name << std::endl;
	os << "entryNumber : " << playerData_.entryNumber << std::endl;
	os << "offence : " << playerData_.offence << std::endl;
	os << "defence : " << playerData_.defence << std::endl;

	return os;
}


