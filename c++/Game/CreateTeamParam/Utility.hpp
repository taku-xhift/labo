/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.11.17 13:56:45
 *
 * @version 0.01, Shishido Takuya, 2010.11.17 13:56:45
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

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
	ランクを求める
	
	スキルによる能力上昇の前
 ============================================================================*/
static unsigned char playerParamGetRankByParam( int position, unsigned char *param);

//! \brief ファイル読込み
//! \note   選手データの読込み
std::vector<Team> readParamFile(std::string fileName);


/**----------------------------------------------------
 * @brief 引数で指定されたデータに関してランダムな数値を作成する
 * @param[in]   average   作成中の選手のポジション
 * @param[in]   sigma     データが欲しいパラメータの名前
 *---------------------------------------------------*/
float gausianRandom(float average, float sigma) throw();


#endif

