
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Team.h"
#include "PlayerData.h"

/**----------------------------------------------------
 * @brief DataSet �^�̃f�[�^���� Team �^�̃f�[�^�����o��
 * @param[in]   dataSet_    �f�[�^
 * @return      �ϊ����ꂽ���ʂ̃f�[�^
 *---------------------------------------------------*/
Team convertFromDataSetToTeam(ReciprocateData* reciprocateData_)
{
	Team team;
	PlayerData* playerArray;
	int i = 0;

	assert(reciprocateData_);
	if (reciprocateData_->type != DATATYPE_PLAYERDATA) {
		assert(0);
	}

	team.playerNumber = reciprocateData_->num;

	for (i = 0; i < reciprocateData_->num; ++i) {
		playerArray = (PlayerData*)reciprocateData_->data[i];
		team.players[i] = *playerArray;
	}

	return team;
}


/**----------------------------------------------------
 * @brief �`�[���̂����U���͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���U����
 *---------------------------------------------------*/
int getTeamOffence(Team* team_)
{
	int offence = 0;
	int i = 0;

	assert(team_);

	for (i = 0; i < team_->playerNumber; ++i) {
		offence += team_->players[i].offence;
	}

	return offence;
}


/**----------------------------------------------------
 * @brief �`�[���̑��h��͂��擾����
 * @param[in]   team_   �v�Z���K�v�ȃ`�[��
 * @return      �`�[���h���
 *---------------------------------------------------*/
int getTeamDefence(Team* team_)
{
	int defence = 0;
	int i = 0;

	assert(team_);

	for (i = 0; i < team_->playerNumber; ++i) {
		defence += team_->players[i].defence;
	}

	return defence;
}



