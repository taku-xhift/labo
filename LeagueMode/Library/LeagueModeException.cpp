/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.07 18:18:08
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/LeagueModeException.hpp"


namespace LeagueMode {

const char* LeagueModeException::what() const throw()
{
	return "LeagueMode::LeagueModeException";
}

const char* BadSelectException::what() const throw()
{
	return "LeagueMode::BadSelectException";
}

}    // namespace LeagueMode

