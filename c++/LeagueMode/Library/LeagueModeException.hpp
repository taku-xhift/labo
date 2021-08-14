
#ifndef LEAGUEMODE_LEAGUEMODEEXCEPTION_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEEXCEPTION_HPP_INCLUDED


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <exception>


namespace LeagueMode {

/**
 * @brief 
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class LeagueModeException : public ::std::exception
{
public:

	/**----------------------------------------------------
	 * @brief ��O������̎擾
	 * @return  ������̐擪�|�C���^
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException


/**
 * @brief �{���I�������͂��������������̂�I�������ꍇ�ɓ��������O
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class BadSelectException : public LeagueModeException
{
public:

	/**----------------------------------------------------
	 * @brief ��O������̎擾
	 * @return  ������̐擪�|�C���^
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException
}    // namespace LeagueMode

#endif

