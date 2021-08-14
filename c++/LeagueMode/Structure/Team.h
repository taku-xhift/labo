
#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "PlayerData.h"
#include "LeagueModeDefineData.h"
#include "ReciprocateData.h"


/**
 * @brief �`�[���f�[�^�����ɂ�������
 * @note    C++ �Ŏg���ۂɂ� TeamForCpp ���������߁B�o�͂��T�|�[�g���Ă����B

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct {
	char            name[256];              //!< �`�[����
	int             playerNumber;           //!< ���ۂɓo�^����Ă���l��


	PlayerData      players[teamNumber];    //!< �I��
} Team;




/**
 * @note �ȉ��AC++ �݊����K�v�Ȃ���
 */
#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief DataSet �^�̃f�[�^���� Team �^�̃f�[�^�����o��
 * @param[in]   dataSet_    �f�[�^
 * @return      �ϊ����ꂽ���ʂ̃f�[�^
 *---------------------------------------------------*/
Team convertFromDataSetToTeam(ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief �`�[���̂����U���͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���U����
 *---------------------------------------------------*/
int getTeamOffence(Team* team_);


/**----------------------------------------------------
 * @brief �`�[���̑��h��͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���h���
 *---------------------------------------------------*/
int getTeamDefence(Team* team_);



#ifdef __cplusplus
}
#endif


#endif

