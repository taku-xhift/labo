
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "LeagueModeException.hpp"


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

