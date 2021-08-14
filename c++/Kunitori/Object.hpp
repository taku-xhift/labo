
#ifndef NEWMODE_OBJECT_HPP_INCLUDED
#define NEWMODE_OBJECT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Math.hpp"

namespace NewMode {

/**
 * @brief �p�����Ă��炤���Ƃ�O��ɂ����N���X
 *          �������̃C���^�[�t�F�[�X�� pure virtual
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

