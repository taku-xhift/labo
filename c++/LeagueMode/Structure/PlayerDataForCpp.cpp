
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "PlayerDataForCpp.hpp"



/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @param[in]  os               �X�g���[���I�u�W�F�N�g
 * @param[in]  playerData_      �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const PlayerData& playerData_)
{
	os << "name : " << playerData_.name << std::endl;
	os << "entryNumber : " << playerData_.entryNumber << std::endl;
	os << "offence : " << playerData_.offence << std::endl;
	os << "defence : " << playerData_.defence << std::endl;

	return os;
}


