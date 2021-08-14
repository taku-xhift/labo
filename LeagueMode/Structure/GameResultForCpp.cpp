
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <cassert>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/GameResultForCpp.hpp"


/**----------------------------------------------------
 * @brief �o�͗p�� operator <<
 * @note       ������Ƌ��������������� TODO
 * @param[in]  os               �X�g���[���I�u�W�F�N�g
 * @param[in]  dataSet_         �o�̓I�u�W�F�N�g
 *---------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const GameResult& gameResult_)
{
	os << "DataType :: GameResult" << std::endl;
// TODO
//	os << "name : " << gameResult_.name << std::endl;
	os << "system time : " << gameResult_.time << std::endl;

	tm* time = localtime(&gameResult_.time);
	os << "year:" << time->tm_year << ", day:" << time->tm_mon << ":" << time->tm_mday <<
		", time:" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << std::endl;

// TODO	
//	os << "score : " << gameResult_.score << std::endl;

	switch (gameResult_.victory) {
		case GAMERESULTCATEGORY_WIN: {
			os << "victory? : Win!"<< std::endl;
			break;
		}
		case GAMERESULTCATEGORY_LOSE: {
			os << "victory? : Lose..."<< std::endl;
			break;
		}
		case GAMERESULTCATEGORY_PKWIN: {
			os << "victory? : PK Win!"<< std::endl;
			break;
		}
		case GAMERESULTCATEGORY_PKLOSE: {
			os << "victory? : PK Lose..."<< std::endl;
			break;
		}
		case GAMERESULTCATEGORY_INVALID: {
			os << "victory? : Invalid Game!!!!"<< std::endl;
			break;
		}
		case GAMERESULTCATEGORY_MAX:
		// �� through down
		default: {
			assert(0);
			break;
		}
	}

	return os;
}




