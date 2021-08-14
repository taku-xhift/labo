
#ifndef NEWMODE_AI_HPP_INCLUDED
#define NEWMODE_AI_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "StreamObject.hpp"
#include "GameData.hpp"
#include <list>

namespace NewMode {

/**
 * @brief �`�h�̋�����S�ĊǗ�����N���X�B���f�Ȃǂ��S�čs���B
 *          �Ǘ������̂̓`�[���B
 *
 * @author  Takuya Shishido
 * @date    2010.01.29 15:47:14
 * @version 0.01, Shishido Takuya, 2010.01.29 15:47:14
 */
class AI
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	AI();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~AI();

private:

	std::list<UserData> userData;      // ���f���s�����߂̃f�[�^������

};    // class AI
}    // namespace NewMode

#endif

