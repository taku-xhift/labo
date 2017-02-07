/**
 * @file
 * @brief 衝突や描画の機構を持ったクラスのベースクラス
 *
 * @author Takuya Shishido
 * @date   2010.01.29 16:05:24
 *
 * @version 0.01, Shishido Takuya, 2010.01.29 16:05:24
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef NEWMODE_OBJECT_HPP_INCLUDED
#define NEWMODE_OBJECT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Math.hpp"

namespace NewMode {

/**
 * @brief 継承してもらうことを前提にしたクラス
 *          いくつかのインターフェースが pure virtual
 *          
 * @author  Takuya Shishido
 * @date    2010.01.29 16:05:24
 * @version 0.01, Shishido Takuya, 2010.01.29 16:05:24
 */
class Object
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	Object();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	virtual ~Object();





	/**----------------------------------------------------
	 * @brief     getter of position
	 * @return    Reference of Vector3 type.
	 *---------------------------------------------------*/
	const Math::Vector3& getPosition() const {
		return this->position;
	}


	/**----------------------------------------------------
	 * @brief        setter of position
	 * @param[in]    position_    A parameter to set.
	 *---------------------------------------------------*/
	void setPosition(const Math::Vector3& position_) {
		this->position = position_;
	}



private:

	Math::Vector3     position;


};    // class Object
}    // namespace NewMode

#endif

