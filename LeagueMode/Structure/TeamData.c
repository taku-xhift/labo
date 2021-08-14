
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"

/**----------------------------------------------------
 * @brief DataSet �^�̃f�[�^���� TeamData �^�̃f�[�^�����o��
 * @param[out]  team_       �Z�b�g��
 * @param[in]   dataSet_    PlayerData �������Ă���f�[�^
 *---------------------------------------------------*/
//void setPlayerDataToTeamData(TeamData* teamData_, ReciprocateData* reciprocateData_)
//{
//	PlayerData* playerArray;
//	int i = 0;
//
//	assert(reciprocateData_);
//	if (reciprocateData_->type != DATATYPE_PLAYERDATA) {
//		assert(0);
//	}
//
//	team_->playerNumber = reciprocateData_->num;
//
//	for (i = 0; i < reciprocateData_->num; ++i) {
//		playerArray = (PlayerData*)reciprocateData_->value[i];
//		team_->players[i] = *playerArray;
//	}
//}


/**----------------------------------------------------
 * @brief �`�[���̂����U���͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���U����
 *---------------------------------------------------*/
int getTeamOffence(TeamData* teamData_)
{
	int offence = 0;
	int i = 0;

	assert(teamData_);

	for (i = 0; i < teamData_->playerNumber; ++i) {
		offence += teamData_->players[i].offence;
	}

	return offence;
}


/**----------------------------------------------------
 * @brief �`�[���̑��h��͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���h���
 *---------------------------------------------------*/
int getTeamDefence(TeamData* teamData_)
{
	int defence = 0;
	int i = 0;

	assert(teamData_);

	for (i = 0; i < teamData_->playerNumber; ++i) {
		defence += teamData_->players[i].defence;
	}

	return defence;
}



