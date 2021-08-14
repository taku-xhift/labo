
#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


/**
 * @brief �`�[���f�[�^�����ɂ�������
 * @note    C++ �Ŏg���ۂɂ� TeamDataForCpp ���������߁B�o�͂��T�|�[�g���Ă����B

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct {
	char            name[256];                      //!< �`�[����
	int             teamID;                         //!< �`�[���p���j�[�N�h�c
	int             playerNumber;                   //!< ���ۂɓo�^����Ă���l��
	PlayerData      players[team_playerNumber];     //!< �I��
} TeamData;




/**
 * @note �ȉ��AC++ �݊����K�v�Ȃ���
 */
#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief DataSet �^�̃f�[�^���� TeamData �^�̃f�[�^�����o��
 * @param[out]  team_       �Z�b�g��
 * @param[in]   dataSet_    PlayerData �������Ă���f�[�^
 *---------------------------------------------------*/
void setPlayerDataToTeamData(TeamData* teamData_, ReciprocateData* reciprocateData_);


/**----------------------------------------------------
 * @brief �`�[���̂����U���͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���U����
 *---------------------------------------------------*/
int getTeamOffence(TeamData* teamData_);


/**----------------------------------------------------
 * @brief �`�[���̑��h��͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���h���
 *---------------------------------------------------*/
int getTeamDefence(TeamData* teamData_);



#ifdef __cplusplus
}
#endif


#endif

