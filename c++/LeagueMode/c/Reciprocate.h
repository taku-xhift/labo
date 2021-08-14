
#ifndef RECIPROCATE_H_INCLUDED
#define RECIPROCATE_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "PlayerData.h"
#include "GameResult.h"


#ifdef __cplusplus
extern "C" {
#endif



/**-------------------------------------------------------------
 * @brief ID �𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       ID_     �I��̓o�^�h�c
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_Number(int ID_);


/**-------------------------------------------------------------
 * @brief ���O�𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       name_   �I��̖��O
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_PlayerName(const char* name_);


/**-------------------------------------------------------------
 * @brief �`�[���̖��O�𗊂�ɁA���̃`�[���ɏ�������I��̃f�[�^�ꗗ��
 *              �c�a �������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]   teamName_           �L�[���[�h
 * @param[out]  reciprocateData_    �o�͐�
 *------------------------------------------------------------*/
void findPlayerData_by_TeamName(const char* teamName_, ReciprocateData* reciprocateData_);


/**-------------------------------------------------------------
 * @brief �������ʂ� perl �ɓn��
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă���B
 * @param[in]   userID_         ���[�U�h�c�B���j�[�N�B
 * @param[out]  gameResult_     ��������
 *------------------------------------------------------------*/
void sendGameResult(int userID_, const GameResult* gameResult_);


#ifdef __cplusplus
}
#endif



#endif

