
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "FileWrite.hpp"
#include "../LeagueModeDefineData.h"
#include "../GameResultForCpp.hpp"


/**-------------------------------------------------------------
 * @brief �����̌��ʂ��t�@�C���ɏ����o���B
 * @param[in]   userID_     �������s�������[�U�̂h�c
 * @param[in]   gameResult  ��������
 *-------------------------------------------------------------*/
void writeFile_GameResult(int userID_, const GameResult* gameResult_)
{
	// �����o�����W���[���쐬
	std::ofstream fileout(dataBaseResultFileName, std::ios::app);

	// �J���Ȃ������ꍇ�͏I��
	if(fileout.fail()) {
		std::cout << dataBaseResultFileName << "cannot open." << std::endl;
		assert(0);
	}

	// �o��
	fileout << "userID = " << userID_ << std::endl;
	fileout << "GameResult = " << (*gameResult_) << std::endl;

	// �t�@�C�������
	fileout.close();
}



