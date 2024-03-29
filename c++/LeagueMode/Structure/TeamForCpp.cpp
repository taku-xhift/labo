
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "TeamForCpp.hpp"
#include "PlayerDataForCpp.hpp"
#ifdef LEAKTEST
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)     // これが重要
#endif

/**----------------------------------------------------
 * @brief 出力用の operator <<
 * @param[in]  os         ストリームオブジェクト
 * @param[in]  team_      出力オブジェクト
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


