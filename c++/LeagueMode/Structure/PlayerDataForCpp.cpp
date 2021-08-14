
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


