
#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LeagueMode �Ŏg����O�N���X�̃x�[�X�N���X
 *          
 * @author  Takuya Shishido
 * @date    2010.04.07 18:18:08
 * @version 0.01, Shishido Takuya, 2010.04.07 18:18:08
 */
class ParseException : public ::std::exception
{
public:

	/**----------------------------------------------------
	 * @brief ��O������̎擾
	 * @return  ������̐擪�|�C���^
	 *---------------------------------------------------*/
	virtual const char* what() const throw();

};    // class LeagueModeException



/**----------------------------------------------------
 * @brief Perl ������󂯎�����f�[�^����͂���
 * @param[in]       reciprocateData_    Perl ����󂯎�����f�[�^
 * @return          reciprocateData_->type �^�̃f�[�^�� void* �ɕϊ���������
 *---------------------------------------------------*/
const void* getKeyValue(const ReciprocateData& reciprocateData_, const char* key, std::vector<int> node_ = std::vector<int>()) throw(ParseException);


#ifdef __cplusplus
}
#endif

#endif

