
#ifndef LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED
#define LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>

namespace LeagueMode {


/**----------------------------------------------------
 * @brief  stringstream ������������֐�
 * @param[in]   ss_     ����������X�g���[��
 *---------------------------------------------------*/
template<typename Type>
void clearStream(Type& ss_)
{
	// �o�b�t�@�N���A
	ss_.str("");
	// �X�g���[���̏�Ԃ��N���A����B���̍s���Ȃ��ƈӐ}�ʂ�ɓ��삵�Ȃ�
	ss_.clear(std::stringstream::goodbit);
}



/**----------------------------------------------------
 * @brief  stringstream ������������֐�
 * @param[in]   ss_     ����������X�g���[��
 *---------------------------------------------------*/
std::vector<std::string> splitString(std::string& string_);




}    // namespace LeagueMode

#endif

