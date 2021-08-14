
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <climits>
#include <malloc.h>
#include <assert.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/CommandCreater_FoundTeamData.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Storage.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief ���������ꂽ�R�}���h�̎擾�֐�
 * @return      ���������ꂽ�R�}���h
 *---------------------------------------------------*/
FoundTeamDataDirection getFoundTeamDataDirection()
{
	FoundTeamDataDirection direction;
	direction.teamName = "";
	direction.teamID = INT_MAX;

	for (int i = 0; i < sizeof(direction.useList)/sizeof(direction.useList[0]); ++i) {
		direction.useList[i] = USELIST_UNUSE;
	}

	return direction;
}


/**----------------------------------------------------
 * @brief �p�����[�^�Z�b�g���W���[��
 * @note    UseList �̊Ǘ����s���̂ŁA���ڑ�������A���̃��W���[����ʂ�����
 * @param[in]   teamID_     �`�[��ID
 *---------------------------------------------------*/
void setTeamID_FoundTeamDataDirection(FoundTeamDataDirection* command_, int teamID_)
{
	command_->teamID = teamID_;
	command_->useList[0] = USELIST_USE;
}


/**----------------------------------------------------
 * @brief �p�����[�^�Z�b�g���W���[��
 * @note    UseList �̊Ǘ����s���̂ŁA���ڑ�������A���̃��W���[����ʂ�����
 * @param[in]   teamName_   �`�[����
 *---------------------------------------------------*/
void setTeanName_FoundTeamDataDirection(FoundTeamDataDirection* command_, const char* teamName_)
{
	command_->teamName = teamName_;
	command_->useList[1] = USELIST_USE;
}


/**----------------------------------------------------
 * @brief �R�}���h�쐬�֐�
 * @note    �擾�����R�}���h�͎����ŉ���֐����g���ĉ�����邱��
 * @param[in]   �w��
 * @return      �쐬���ꂽ�R�}���h
 *---------------------------------------------------*/
ReciprocateData* commandCreate_FoundTeamData(FoundTeamDataDirection* direction_)
{
	ReciprocateData* command = reinterpret_cast<ReciprocateData*>(calloc(1, sizeof(ReciprocateData)));

	command->type = DATATYPE_STRUCT;
	command->key = key_TeamData;

	// �v�f���𐔂���
	int useCount = 0;
	for (int i = 0; i < sizeof(direction_->useList)/sizeof(direction_->useList[0]); ++i) {
		if (direction_->useList[i] == USELIST_USE) {
			++useCount;
		}
	}
	command->num = useCount;

	if (direction_->useList[0] = USELIST_USE) {
		command->value = reinterpret_cast<void**>(calloc(command->num, sizeof(void**)));
		command->value[useCount-1] = storage_Int(direction_->teamID, key_TeamData_ID);
		--useCount;
	}

	if (direction_->useList[1] == USELIST_USE) {
		command->value = reinterpret_cast<void**>(calloc(command->num, sizeof(void**)));
		command->value[useCount-1] = storage_String(direction_->teamName, key_TeamData_name);
		--useCount;
	}

	if (useCount != 0) {
		// ������������������Ȃ�����
		assert(0);
	}

	return command;
}




