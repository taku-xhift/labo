
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <malloc.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/DB/fileRead.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Storage.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	std::string dataFileName = "game_para.csv";     //!< �f�[�^�x�[�X�Ƃ��Ďg���t�@�C���̖��O
	const int teamNameDataNumber = 0;               //!< �`�[���l�[���������Ă���ԍ�
	const int entryNumberDataNumber = 4;            //!< �I��̊Ǘ��ԍ��������Ă���ԍ�
	const int playerNameDataNumber = 5;             //!< �I��̊Ǘ��ԍ��������Ă���ԍ�
	const int offenceDataNumber = 25;               //!< �I�t�F���X�̃f�[�^�������Ă���ԍ�
	const int defenceDataNumber = 26;               //!< �f�B�t�F���X�̃f�[�^�������Ă���ԍ�
}




/**----------------------------------------------------
 * @brief �t�@�C������`�[���̖��O�𗊂�ɑI��f�[�^��ǂݍ���
 * @note    ����͖{�� Perl �ōs����ׂ������̂͂������A
 *              ��s���� cpp �ɂč쐬�B
 *              perl ���ǂ������炻����ɒu�������ׂ��B
 * @param[in]   teamName_           �T���`�[����
 * @param[out]  reciprocateData_    �f�[�^�i�[���s���ꏊ�B
 *                                      ����� C �� perl �̃f�[�^�̂������s�����߂̃f�[�^�B
 *---------------------------------------------------*/
void readFile_TeamDataInformation(const char* teamName_, ReciprocateData* reciprocateData_)
{
	assert(reciprocateData_);

	std::ifstream ifs(dataFileName.c_str());
	std::string fileData;

	// �t�@�C�����ǂݍ��߂����`�F�b�N���s��
	assert(ifs.good());

	// �f�[�^�̊m��
	std::vector<std::vector<std::string> > playerDataContainer;
	while (std::getline(ifs, fileData)) {
		std::vector<std::string> dataName = LeagueMode::splitString(fileData);
		//boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// ���O���w�肳�ꂽ���̂ƈ�v�����Ƃ��̂݃f�[�^���m��
		if (dataName[teamNameDataNumber] == teamName_) {
			playerDataContainer.push_back(dataName);
		}
	}

	// �z��I�[�o�[���N�����Ȃ����`�F�b�N�B
	// reciprocateData_ �ɂ͂��炩���߃��������m�ۂ���Ă���B
	// �����œ��I�ɃT�C�Y���m�ۂ��Ă����[�J���I�u�W�F�N�g�Ɛf�f����A
	// �֐����o�鍠�ɂ͏����Ă��܂��c
	if (playerDataContainer.size() > team_playerNumber) {
		// �`�[���\�萔�𒴂��Ă��܂��܂����B���̂܂ܐi�ނƔz��I�[�o�[���N���܂�
		assert(0);
	}

	// �ǂݎ�����f�[�^��ۑ�
	reciprocateData_->num = playerDataContainer.size();
	reciprocateData_->type = DATATYPE_STRUCT;

	TeamData teamData;
	teamData.playerNumber = playerDataContainer.size();

	strcpy(teamData.name, teamName_);
	std::istringstream is;
	for (unsigned int i = 0; i < teamData.playerNumber; ++i) {
		LeagueMode::clearStream(is);
		strcpy(teamData.players[i].name, playerDataContainer.at(i).at(playerNameDataNumber).c_str());
		is.str(playerDataContainer.at(i).at(entryNumberDataNumber));
		is >> teamData.players[i].entryNumber;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(offenceDataNumber));
		is >> teamData.players[i].offence;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(defenceDataNumber));
		is >> teamData.players[i].defence;
	}

	ReciprocateData* temp = storage_TeamData(teamData, key_TeamData);

	memmove(reciprocateData_, temp, sizeof(ReciprocateData));

	free(temp);


/*
	reciprocateData_->value = (void**)calloc(playerDataContainer.size() , sizeof(PlayerData));
	PlayerData* array = (PlayerData*)calloc(playerDataContainer.size() , sizeof(PlayerData));


	std::istringstream is;
	for (unsigned int i = 0; i < playerDataContainer.size(); ++i) {
		LeagueMode::clearStream(is);
		strcpy(array[i].name, playerDataContainer.at(i).at(playerNameDataNumber).c_str());
		is.str(playerDataContainer.at(i).at(entryNumberDataNumber));
		is >> array[i].entryNumber;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(offenceDataNumber));
		is >> array[i].offence;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(defenceDataNumber));
		is >> array[i].defence;
	}

	for (unsigned int i = 0; i < playerDataContainer.size(); ++i) {
		reciprocateData_->value[i] = (void*)&array[i];
	}
*/
	//reciprocateData_->address = reinterpret_cast<unsigned int>(array);
}



