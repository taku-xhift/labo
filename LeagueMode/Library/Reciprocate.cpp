/**
 * @file
 * @brief �C���^�[�t�F�[�X�����B
 * @note    �������Ăb���ł̓f�[�^�̂������s���B
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Reciprocate.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Converter.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/DB/FileRead.hpp"
//#include "FileWrite.hpp"




/**-------------------------------------------------------------
 * @brief ID �𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       command_    �R�}���h�itype=INT,value=playerNumber�j
 * @param[out]      data_       �f�[�^�i�[��
 * @return          �c�a�G���[�̓��e
 *------------------------------------------------------------*/
DBError findPlayerData_by_Number(ReciprocateData* command_, PlayerData* data_)
{
	DBError error;
	return error;
}


/**-------------------------------------------------------------
 * @brief ���O�𗊂�� �c�a ����f�[�^������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       command_    �R�}���h�itype=STRING,value=playerName�j
 * @param[out]      data_       �f�[�^�i�[��
 * @return          �c�a�G���[�̓��e
 *------------------------------------------------------------*/
DBError findPlayerData_by_PlayerName(ReciprocateData* command_, PlayerData* playerData_)
{
	DBError error;
	return error;
}



/**-------------------------------------------------------------
 * @brief �`�[���̖��O�𗊂�ɁA���̃`�[���ɏ�������I��̃f�[�^�ꗗ��
 *              �c�a �������Ă���
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă��āA
 *              �Ԃ�l�͂���ɂ���ē���ꂽ�f�[�^
 * @param[in]       command_    �R�}���h
 * @param[out]      data_       �f�[�^�i�[��
 * @return          �c�a�G���[�̓��e
 *------------------------------------------------------------*/
#define USE_PERL 0

DBError findPlayerDataByTeamName(ReciprocateData* command_, TeamData* teamData_)
{
	DBError error;

	// ��������f�[�^���s���ł���΃R�}���h�쐬���ɖ�肠��
	if (command_ == NULL || teamData_ == NULL) {
		strcpy(error.error, DBErr_CommandError);
		return error;
	}

	ReciprocateData* data = createReciprocateData();

	// TODO
	// ��c����ɏ������������肢����������
	// data �̃A�h���X�Ƀf�[�^���쐬���Ă��炢����
	{
		// �`�[���̖��O����Ƃ�ɍs��
		// ������Ȃ���΃R�}���h�쐬�̃G���[
		const char* teamName;
		try {
			teamName = reinterpret_cast<const char*>(getKeyValue(*command_, key_TeamData_name));
		} catch (ParseException) {
			assert(0);
			strcpy(error.error, DBErr_CommandError);
			return error;
		}

		readFile_TeamDataInformation(teamName, data);
	}

#if USE_PERL
	// error ��T���ɂ������A������Ȃ���΂c�a�̃G���[
	try {
		strcpy(error.error, reinterpret_cast<const char*>(getKeyValue(*data, key_DBError)));
	} catch (ParseException) {
		strcpy(error.error, DBErr_DBError);
		return error;
	}
#else
	strcpy(error.error, DBErr_NoError);
#endif

	// ��肪������΃f�[�^�̊i�[
	if (strcmp(error.error, DBErr_NoError) == 0) {
#if USE_PERL
		error = convertToDBError(data);
#endif
		const ReciprocateData* temp = reinterpret_cast<const ReciprocateData*>(getKeyValue(*data, key_TeamData));
		*teamData_ = convertToTeamData(temp);
	} else {
		// ���͂���悤�����A�z��O�̂��̂̂悤
		assert(0);
	}

	releaseReciprocateData(data);

	return error;
}


/**-------------------------------------------------------------
 * @brief �������ʂ� perl �ɓn��
 * @note    �C���[�W�I�ɂ͂���̎����� perl �ƂȂ����Ă���B
 * @param[in]       command_    �R�}���h�itype=string,value=teamName�j
 * @return          �c�a�G���[�̓��e
 *------------------------------------------------------------*/
DBError sendGameResult(ReciprocateData* command_)
{
	assert(command_);
	//writeFile_GameResult(userID_, gameResult_);
	DBError error;
	return error;
}



