
#ifndef FILEWRITE_HPP_INCLUDED
#define FILEWRITE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "../GameResult.h"


#ifdef __cplusplus
extern "C" {
#endif

/**-------------------------------------------------------------
 * @brief �����̌��ʂ��t�@�C���ɏ����o���B
 * @param[in]   userID_     �������s�������[�U�̂h�c
 * @param[in]   gameResult  ��������
 *-------------------------------------------------------------*/
void writeFile_GameResult(int userID_, const GameResult* gameResult_);

#ifdef __cplusplus
}
#endif


#endif

