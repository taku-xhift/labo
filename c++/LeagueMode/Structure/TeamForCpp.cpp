
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "TeamForCpp.hpp"
#include "PlayerDataForCpp.hpp"
#ifdef LEAKTEST
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)     // ���ꂪ�d�v
#endif

/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @param[in]  os         �X�g���[���I�u�W�F�N�g
 * @param[in]  team_      �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const Team& team_)
{
	os << "Team Information" << std::endl;
	os << "name : " << team_.name << std::endl;
	os << "playerNumber : " << team_.playerNumber << std::endl;
	os << "playerData:" << std::endl;

	for (int i = 0; i < team_.playerNumber; ++i) {
		os << "player[" << i << "] : " << std::endl;
		os << team_.players[i] << std::endl;
	}

	return os;
}


