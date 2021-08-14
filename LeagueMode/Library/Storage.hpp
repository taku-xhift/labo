
#ifndef STORAGE_HPP_INCLUDED
#define STORAGE_HPP_INCLUDED

//-----------------------------------------------------
//  includ
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"


/**----------------------------------------------------
 * @brief �f�[�^�i�[���ς񂾃f�[�^�� error ����t������
 * @note        �`�F�b�N�p�B�{���b������ error �����Ċi�[���邱�Ƃ͂Ȃ��͂��c
 * @param[in]   data_   ��ʂ�̃f�[�^�̊i�[���ς񂾃f�[�^
 * @return      data_ �� error �������f�[�^
 *---------------------------------------------------*/
ReciprocateData* bindDataOnWithError(ReciprocateData* data_, const char* errorWord_);



/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_Int(int data_, const char* key_);


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_String(const char* data_, const char* key_);


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_Error(const char* data_, const char* key_);


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_PlayerData(const PlayerData& data_, const char* key_);


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_PlayerDataArray(const std::vector<PlayerData>& data_, const char* key_);


/**----------------------------------------------------
 * @brief �f�[�^�i�[
 * @param[in]   data_   �i�[����f�[�^
 * @param[in]   key_    �L�[
 * @return      data_ ����菑���ɕ���Ċi�[�����f�[�^�̃A�h���X
 *---------------------------------------------------*/
ReciprocateData* storage_TeamData(const TeamData& data_, const char* key_);


#endif

