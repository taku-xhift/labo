
#ifndef FILEREAD_HPP_INCLUDED
#define FILEREAD_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"

#ifdef __cplusplus
extern "C" {
#endif



/**----------------------------------------------------
 * @brief �t�@�C������`�[���̖��O�𗊂�ɑI��f�[�^��ǂݍ���
 * @note    ����͖{�� Perl �ōs����ׂ������̂͂������A
 *              ��s���� cpp �ɂč쐬�B
 *              perl ���ǂ������炻����ɒu�������ׂ��B
 * @param[in]   teamName_           �T���`�[����
 * @param[out]  reciprocateData_    �f�[�^�i�[���s���ꏊ�B
 *                                      ����� C �� perl �̃f�[�^�̂������s�����߂̃f�[�^�B
 *---------------------------------------------------*/
void readFile_TeamDataInformation(const char* teamName_, ReciprocateData* reciprocateData_);

#ifdef __cplusplus
}
#endif


#endif

