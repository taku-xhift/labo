
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
 * @brief  ���S�� delete �����邽�߂̕⏕�֐�
 * @param[in]   data_   ���������f�[�^
 *---------------------------------------------------*/
template<typename Type>
void safeDelete(Type* data_)
{
	if (data_ != NULL) {
		delete data_;
		data_ = NULL;
	}
}


/**----------------------------------------------------
 * @brief string �� "," �ɂĕ������A������R���e�i�ɂ��ĕԂ��֐�
 * @note    ��{�I�� csv �t�@�C����ǂݍ��ނ̂Ɏg���܂��傤�B
 *              �g����Ȃ� boost �� split ��������g���Ă��������B
 *              boost ���g���Ȃ����ɔ����č쐬�������̂Ȃ̂ŁB
 *              �܂��A����ɏ������Ă���̂ŁA"," �͔r������Ă��܂��B
 * @param[in]   �Q�l�ɂ��镶����
 * @return      , ����ɕ������ꂽ������Q
 *---------------------------------------------------*/
std::vector<std::string> splitString(const std::string& strings_);


}    // namespace LeagueMode

#endif

