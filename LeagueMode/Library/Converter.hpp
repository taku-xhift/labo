
#ifndef CONVERTER_HPP_INCLUDED
#define CONVERTER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/DBError.h"


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
DBError convertToDBError(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
PlayerData convertToPlayerData(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    ��͂��K�v�ȃf�[�^
 * @para[in]    node_               �z��̏ꍇ�͗~�����f�[�^�̔ԍ����w��B
 * @return      ��͂̌��ʓ���ꂽ�f�[�^�B
 *                  �z��Ȃ�� node_ �̐擪�Ŏw�肳�ꂽ�f�[�^�B
 *---------------------------------------------------*/
TeamData convertToTeamData(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());


#endif

