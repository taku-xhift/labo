
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"

namespace LeagueMode {



/**----------------------------------------------------
 * @brief string �� "," �ɂĕ������A������R���e�i�ɂ��ĕԂ��֐�
 * @note    ��{�I�� csv �t�@�C����ǂݍ��ނ̂Ɏg���܂��傤�B
 *              �g����Ȃ� boost �� split ��������g���Ă��������B
 *              boost ���g���Ȃ����ɔ����č쐬�������̂Ȃ̂ŁB
 *              �܂��A����ɏ������Ă���̂ŁA"," �͔r������Ă��܂��B
 * @param[in]   �Q�l�ɂ��镶����
 * @return      , ����ɕ������ꂽ������Q
 *---------------------------------------------------*/
std::vector<std::string> splitString(const std::string& strings_)
{
	std::vector<std::string> container;
	unsigned int num = 0;
	std::string temp = strings_;

	while (true) {
		num = temp.find(",", 0);
		if (num == std::string::npos) {
			container.push_back(temp);
			return container;
		}
		container.push_back(temp.substr(0, num));

		temp.erase(0, num+1);
	}

	return container;
}


}    // namespace LeagueMode

