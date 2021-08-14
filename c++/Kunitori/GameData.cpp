
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "GameData.hpp"


namespace NewMode {


/**--------------------------------------------------------
 * @brief        unset havingTeam
 * @param[in]    teamID     äOÇµÇΩÇ¢É`Å[ÉÄÇÃID
 * @exception    FindError  å©Ç¬Ç©ÇÁÇ»Ç©Ç¡ÇΩ
 *-------------------------------------------------------*/
void UserData::unsetHavingTeamID(int teamID_) throw(Error::FindError)
{
	std::list<int>::iterator ite = std::find(this->havingTeamID.begin(), this->havingTeamID.end(), teamID_);

	if (ite == this->havingTeamID.end()) {
		throw Error::FindError();
	}

	this->havingTeamID.erase(ite);
}


}   // namespace NewMode

