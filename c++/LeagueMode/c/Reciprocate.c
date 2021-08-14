
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Reciprocate.h"
#include "DB/FileRead.hpp"
#include "DB/FileWrite.hpp"



/**-------------------------------------------------------------
 * @brief ID �𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       ID_     �I��̓o�^�h�c
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_Number(int ID_)
{
	PlayerData data;
	return data;
}


/**-------------------------------------------------------------
 * @brief ���O�𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       name_   �I��̖��O
 *------------------------------------------------------------*/
PlayerData findPlayerData_by_PlayerName(const char* name_)
{
	PlayerData data;
	return data;
}



/**-------------------------------------------------------------
 * @brief �`�[���̖��O�𗊂�ɁA���̃`�[���ɏ�������I��̃f�[�^�ꗗ��
 *              �c�a �������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]   teamName_           �L�[���[�h
 * @param[out]  reciprocateData_    �o�͐�
 *------------------------------------------------------------*/
void findPlayerData_by_TeamName(const char* teamName_, ReciprocateData* reciprocateData_)
{
	assert(reciprocateData_);
	readFile_TeamInformation(teamName_, reciprocateData_);
}


/**-------------------------------------------------------------
 * @brief �������ʂ� perl �ɓn��
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă���B
 * @param[in]   userID_         ���[�U�h�c�B���j�[�N�B
 * @param[out]  gameResult_     ��������
 *------------------------------------------------------------*/
void sendGameResult(int userID_, const GameResult* gameResult_)
{
	assert(gameResult_);
	writeFile_GameResult(userID_, gameResult_);
}



