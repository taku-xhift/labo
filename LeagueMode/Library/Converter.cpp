
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Converter.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
DBError convertToDBError(const ReciprocateData* reciprocateData_, std::vector<int> node_ /*= std::vector<int>()*/)
{
	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// �z��łȂ��\��������B�������͎w��̃~�X
			assert(0);
		}
	}

	DBError data;

	strcpy(data.error, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_DBError, node_)));

	return data;
}



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
PlayerData convertToPlayerData(const ReciprocateData* reciprocateData_, std::vector<int> node_ /* = std::vector<int>()*/)
{
	if (reciprocateData_->type != DATATYPE_STRUCT
		&& reciprocateData_->type != DATATYPE_STRUCTARRAY)
	{
		// �n����Ă���f�[�^���s���Ȃ��̂̉\��������
		assert(0);
	}

	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// �z��łȂ��\��������B�������͎w��̃~�X
			assert(0);
		}
	}

	PlayerData data;

	strcpy(data.name, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_PlayerData_player_name, node_)));
	data.entryNumber = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_player_id, node_));
	data.offence = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_offence, node_));
	data.defence = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_defence, node_));

	return data;
}



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
TeamData convertToTeamData(const ReciprocateData* reciprocateData_, std::vector<int> node_ /* = std::vector<int>()*/)
{
	if (reciprocateData_->type != DATATYPE_STRUCT
		&& reciprocateData_->type != DATATYPE_STRUCTARRAY)
	{
		// �n����Ă���f�[�^���s���Ȃ��̂̉\��������
		assert(0);
	}

	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// �z��łȂ��\��������B�������͎w��̃~�X
			assert(0);
		}
	}

	TeamData data;

	strcpy(data.name, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_TeamData_name, node_)));
	data.teamID = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_TeamData_ID, node_));
	data.playerNumber = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_TeamData_playerNumber, node_));

	for (int i = 0; i < data.playerNumber; ++i) {
		// �����Ŏw�肳�ꂽ node_ �́ATeamData ���g���z�񂾂����ꍇ�̂��́B
		// localNode �����̂́Astruct TeamData �ł͂���ɂ��̐�� PlayerData �^�̔z�񂪑҂��Ă��āA
		// ������w�肷�邽�߂Ƀ��[�v���񂵂Ȃ��� localNode �𖈉�쐬���Ȃ����Ă���
		std::vector<int> localNode(node_);
		localNode.push_back(i);

		data.players[i] = convertToPlayerData(reciprocateData_, localNode);
	}

	return data;
}




