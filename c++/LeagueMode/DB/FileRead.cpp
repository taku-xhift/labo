
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include "../LeagueModeDefineData.h"
#include "../ReciprocateData.h"
#include "../ReciprocateDataForCpp.hpp"
#include "fileRead.hpp"
#include "../PlayerDataForCpp.hpp"
#include "../UtilityFunction.hpp"
#include "../LeagueModeDefineData.h"
#include "../MemoryLeakCheck.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	std::string dataFileName = "game_para.csv";     //!< �f�[�^�x�[�X�Ƃ��Ďg���t�@�C���̖��O
	const int teamNameDataNumber = 0;               //!< �`�[���l�[���������Ă���ԍ�
	const int entryNumberDataNumber = 1;            //!< �I��̊Ǘ��ԍ��������Ă���ԍ�
	const int playerNameDataNumber = 2;             //!< �I��̊Ǘ��ԍ��������Ă���ԍ�
	const int offenceDataNumber = 3;               //!< �I�t�F���X�̃f�[�^�������Ă���ԍ�
	const int defenceDataNumber = 4;               //!< �f�B�t�F���X�̃f�[�^�������Ă���ԍ�
}


void readFile_TeamInformation(const char* teamName_, ReciprocateData* reciprocateData_)
{
	assert(reciprocateData_);

	std::ifstream ifs(dataFileName.c_str());
	std::string fileData;

	// �t�@�C�����ǂݍ��߂����`�F�b�N���s��
	assert(ifs.good());

	// �f�[�^�̊m��
	std::vector<std::vector<std::string> > playerDataContainer;
	while (std::getline(ifs, fileData)) {
		std::vector<std::string> dataName;
		boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// ���O���w�肳�ꂽ���̂ƈ�v�����Ƃ��̂݃f�[�^���m��
		if (dataName[teamNameDataNumber] == teamName_) {
			playerDataContainer.push_back(dataName);
		}
	}

	// �z��I�[�o�[���N�����Ȃ����`�F�b�N�B
	// reciprocateData_ �ɂ͂��炩���߃��������m�ۂ���Ă���B
	// �����œ��I�ɃT�C�Y���m�ۂ��Ă����[�J���I�u�W�F�N�g�Ɛf�f����A
	// �֐����o�鍠�ɂ͏����Ă��܂��c
	if (playerDataContainer.size() > teamNumber) {
		// �`�[���\�萔�𒴂��Ă��܂��܂����B���̂܂ܐi�ނƔz��I�[�o�[���N���܂�
		assert(0);
	}

	// �ǂݎ�����f�[�^��ۑ�
	reciprocateData_->num = playerDataContainer.size();
	reciprocateData_->type = DATATYPE_PLAYERDATA;
	reciprocateData_->data = (void**)calloc(playerDataContainer.size() , sizeof(PlayerData));
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
		reciprocateData_->data[i] = (void*)&array[i];
	}

	reciprocateData_->address = reinterpret_cast<unsigned int>(array);
}



