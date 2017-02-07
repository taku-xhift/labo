/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2009.10.28 08:51:29
 *
 * @version 0.01, Shishido Takuya, 2009.10.28 08:51:29
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


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

