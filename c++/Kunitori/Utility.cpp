
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include "Utility.hpp"
#include "GameManager.hpp"
#include "City.hpp"
#include "StreamObject.hpp"


using namespace so;

namespace Utility {


/**--------------------------------------------------------
 * @brief �������f�[�^�ǂݍ���
 * @author  Takuya Shishido
 * @date    2009.11.08 21:13:39
 * @version 0.01, Shishido Takuya, 2009.11.08 21:13:39
 --------------------------------------------------------*/
// TODO
// ���L�֐������̕�����Q�����ׂĎ����B
// ����� CityParameter �� TeamParameter, UserData �܂�
// ���ׂĂɑΉ�����\��B
// template ���g���Ȃǂ��Ă��܂����悤�ɂ������Ƃ���ł����B
	void readInitFile(NewMode::GameManager& manager)
{
	std::string fileName = manager.getCityConfigFileName();

	std::ifstream ifs(fileName.c_str());
	std::string data;
	NewMode::CityParameter cityParameter;    // ����Ƀf�[�^��������

/*	while (getline(ifs, data)) {
		unsigned int equalPos = std::string part = data.find("=", 0);
		std::string dataName = data.substr(0, equalPos);
		if (dataName.empty() == true) {
			out << "�v�f�̖��O�̖����f�[�^���݂���܂����B" << endl;
			out << "�ǂݍ��݂𒆎~���܂��B" << endl;
			return;
		}

		std::string valueStr = data.stbstr(equalPos);
		int value = atoi(valueStr.c_str());
		if (value == 0) {
			out << "0 ���ǂݍ��܂�܂����B" << endl;
			out << "�s���ȃf�[�^���������\��������܂��B" << endl;
		}

		//assortmentData(cityParameter, dataName, value);

		// find_first_not_of(" ", 0) �ŃX�y�[�X�ȊO�̃f�[�^�̐擪��T���o��
		// ���̕����������؂�o���A����� atoi �Ő��l���B
		// atoi == 0 �Ȃ當���񂪓n����Ă���̂Ŏ��s
		// ���l�ɂȂ��Ă���� ����� dataName �Ŏw�肳�ꂽ�p�����[�^�ɑ΂��ď�����
		// end �Ȃǂ̓��蕶������f�[�^�Z�b�g�̖��[�̎w�肵�ɂ����
		// ���̒i�K�Őݒ肳�ꂽ�p�����[�^�� gameManager �̃f�[�^�R���e�i��
		// �R�s�[���ďI���B

		// ��L�̍�Ƃ� eof �܂ő����čs���A���ׂēǂݍ��ݏI������I��

		out << data << endl;
	}
	*/
}


}


