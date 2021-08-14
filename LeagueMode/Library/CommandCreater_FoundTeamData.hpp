
#ifndef COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED
#define COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	USELIST_USE,
	USELIST_UNUSE,
} UseList;


/**
 * @brief �`�[�������c�a����擾���邽�߂̌����w��
 *          
 * @note    �p�����[�^�̂����A�Е��������w�肳��Ă���΂���Ō�������
 *              �����ɐ��藧���Ȃ����̗̂D��x�̓����o�̏ォ�珇�B
 * @author  Takuya Shishido
 * @date    2010.04.22 13:19:35
 * @version 0.01, Shishido Takuya, 2010.04.22 13:19:35
 */
typedef struct
{
	int         teamID;         //!< �����F�`�[���̃��j�[�N�h�c�B�w�肵�Ȃ��Ȃ� INT_MAX �ɂ��邱��
	const char* teamName;       //!< �����F�`�[���̖��O

	UseList     useList[2];     //!< �g�p���g�p�̃t���O���X�g
} FoundTeamDataDirection;




/**----------------------------------------------------
 * @brief ���������ꂽ�R�}���h�̎擾�֐�
 * @note    UseList �̊Ǘ����s���̂ŁA���ڑ�������A���̃��W���[����ʂ�����
 * @return      ���������ꂽ�R�}���h
 *---------------------------------------------------*/
FoundTeamDataDirection getFoundTeamDataDirection();


/**----------------------------------------------------
 * @brief �p�����[�^�Z�b�g���W���[��
 * @note    UseList �̊Ǘ����s���̂ŁA���ڑ�������A���̃��W���[����ʂ�����
 * @param[in]   teamID_     �`�[��ID
 *---------------------------------------------------*/
void setTeamID_FoundTeamDataDirection(FoundTeamDataDirection* command_, int teamID_);


/**----------------------------------------------------
 * @brief �p�����[�^�Z�b�g���W���[��
 * @param[in]   teamName_   �`�[����
 *---------------------------------------------------*/
void setTeanName_FoundTeamDataDirection(FoundTeamDataDirection* command_, const char* teamName_);


/**----------------------------------------------------
 * @brief �R�}���h�쐬�֐�
 * @note    �擾�����R�}���h�͎����ŉ���֐����g���ĉ�����邱��
 * @param[in]   �w��
 * @return      �쐬���ꂽ�R�}���h
 *---------------------------------------------------*/
ReciprocateData* commandCreate_FoundTeamData(FoundTeamDataDirection* direction_);



#ifdef __cplusplus
}
#endif

#endif  // COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED

