
#ifndef NEWMODE_GOVERNOR_HPP_INCLUDED
#define NEWMODE_GOVERNOR_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <list>
#include "City.hpp"

namespace NewMode {

/**
 * @brief äXÇä«óùÇ∑ÇÈÇΩÇﬂÇÃÉNÉâÉX
 *          
 * @author  Takuya Shishido
 * @date    2010.01.29 18:04:44
 * @version 0.01, Shishido Takuya, 2010.01.29 18:04:44
 */
class Governor
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	Governor();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~Governor();

private:

	std::list<City>     cityList;

};    // class Governor
}    // namespace NewMode

#endif

