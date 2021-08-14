
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "GameData.hpp"


namespace NewMode {


/**--------------------------------------------------------
 * @brief        unset havingTeam
 * @param[in]    teamID     �O�������`�[����ID
 * @exception    FindError  ������Ȃ�����
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

