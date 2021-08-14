
#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#pragma warning(disable:4996)
#pragma warning(disable:4290)

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <stdexcept>
#include "DataType.hpp"


PosList posConverter(std::string pos) throw(std::invalid_argument);
std::string posConverter(PosList pos) throw(std::invalid_argument);
bool converterFromStarToBoolean(std::string star) throw(std::invalid_argument);

void sortAsLigaEspanola2010(const std::vector<Team>& original, std::vector<Team>& sorted) throw();
void sortAsLigaEspanola2011(const std::vector<Team>& original, std::vector<Team>& sorted) throw();
void sortAsPremierLeague2010(std::vector<Team>& original, std::vector<Team>& sorted) throw();
/*============================================================================
	�����N�����߂�
	
	�X�L���ɂ��\�͏㏸�̑O
 ============================================================================*/
static unsigned char playerParamGetRankByParam( int position, unsigned char *param);

//! \brief �t�@�C���Ǎ���
//! \note   �I��f�[�^�̓Ǎ���
std::vector<Team> readParamFile(std::string fileName);


/**----------------------------------------------------
 * @brief �����Ŏw�肳�ꂽ�f�[�^�Ɋւ��ă����_���Ȑ��l���쐬����
 * @param[in]   average   �쐬���̑I��̃|�W�V����
 * @param[in]   sigma     �f�[�^���~�����p�����[�^�̖��O
 *---------------------------------------------------*/
float gausianRandom(float average, float sigma) throw();


#endif

