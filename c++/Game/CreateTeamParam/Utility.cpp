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
#include "Utility.hpp"
#include <map>
#include <stdlib.h>
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Functor.hpp"


PosList posConverter(std::string pos) throw(std::invalid_argument) {
	if (pos.compare("GK") == 0) {
		return PosList_GK;
	} else if (pos.compare("CB") == 0) {
		return PosList_CB;
	} else if (pos.compare("SB") == 0) {
		return PosList_SB;
	} else if (pos.compare("DMF") == 0) {
		return PosList_DMF;
	} else if (pos.compare("SMF") == 0) {
		return PosList_SMF;
	} else if (pos.compare("ST") == 0) {
		return PosList_ST;
	} else if (pos.compare("CF") == 0) {
		return PosList_CF;
	} else if (pos.compare("CMF") == 0) {
		return PosList_CMF;
	} else if (pos.compare("OMF") == 0) {
		return PosList_OMF;
	} else if (pos.compare("SW") == 0) {
		return PosList_SW;
	} else if (pos.compare("WG") == 0) {
		return PosList_WG;
	} else if (pos.compare("WB") == 0) {
		return PosList_WG;
	} else {
		assert(0);
		throw std::invalid_argument("invalidArg => " + pos);
	}
}
std::string posConverter(PosList pos) throw(std::invalid_argument) {
	switch(pos) {
		case PosList_GK: {
			return "GK";
		}
		case PosList_CB: {
			return "CB";
		}
		case PosList_SB: {
			return "SB";
		}
		case PosList_DMF: {
			return "DMF";
		}
		case PosList_SMF: {
			return "SMF";
		}
		case PosList_ST: {
			return "ST";
		}
		case PosList_CF: {
			return "CF";
		}
		case PosList_CMF: {
			return "CMF";
		}
		case PosList_OMF: {
			return "OMF";
		}
		case PosList_SW: {
			return "SW";
		}
		case PosList_WG: {
			return "WG";
		}
		case PosList_WB: {
			return "WB";
		}
		default: {
			assert(0);
			throw std::invalid_argument("invalidArg = " + boost::lexical_cast<std::string>(pos));
		}
	}
}

bool converterFromStarToBoolean(std::string star) throw(std::invalid_argument) {
	if (star.compare("★") == 0) {
		return true;
	} else {
		if (star.compare("") != 0) {
			throw std::invalid_argument(ExceptionMessage("not ★ and \" \"!!!"));
		} else {
			return false;
		}
	}
}

void sortAsLigaEspanola2010(const std::vector<Team>& original, std::vector<Team>& sorted) throw() {
	sorted.resize(original.size());

	for (std::vector<Team>::const_iterator ite = original.begin(); ite != original.end(); ++ite) {
		if (ite->team().compare("バルセロナ") == 0) {
			sorted.at(0) = *ite;
			//sorted.at(0).goal(98);
			//sorted.at(0).lost(24);
		} else if (ite->team().compare("レアル マドリー") == 0) {
			sorted.at(1) = *ite;
			//sorted.at(1).goal(102);
			//sorted.at(1).lost(35);
		} else if (ite->team().compare("バレンシア") == 0) {
			sorted.at(2) = *ite;
			//sorted.at(2).goal(59);
			//sorted.at(2).lost(40);
		} else if (ite->team().compare("セビージャ") == 0) {
			sorted.at(3) = *ite;
			//sorted.at(3).goal(65);
			//sorted.at(3).lost(49);
		} else if (ite->team().compare("マジョルカ") == 0) {
			sorted.at(4) = *ite;
			//sorted.at(4).goal(59);
			//sorted.at(4).lost(44);
		} else if (ite->team().compare("ヘタフェ") == 0) {
			sorted.at(5) = *ite;
			//sorted.at(5).goal(58);
			//sorted.at(5).lost(48);
		} else if (ite->team().compare("ビジャレアル") == 0) {
			sorted.at(6) = *ite;
			//sorted.at(6).goal(58);
			//sorted.at(6).lost(57);
		} else if (ite->team().compare("アスレティック ビルバオ") == 0) {
			sorted.at(7) = *ite;
			//sorted.at(7).goal(50);
			//sorted.at(7).lost(53);
		} else if (ite->team().compare("アトレティコ マドリー") == 0) {
			sorted.at(8) = *ite;
			//sorted.at(8).goal(57);
			//sorted.at(8).lost(61);
		} else if (ite->team().compare("デポルティーボ ラ コルーニャ") == 0) {
			sorted.at(9) = *ite;
			//sorted.at(9).goal(35);
			//sorted.at(9).lost(49);
		} else if (ite->team().compare("エスパニョール") == 0) {
			sorted.at(10) = *ite;
			//sorted.at(10).goal(29);
			//sorted.at(10).lost(46);
		} else if (ite->team().compare("オサスナ") == 0) {
			sorted.at(11) = *ite;
			//sorted.at(11).goal(37);
			//sorted.at(11).lost(46);
		} else if (ite->team().compare("アルメリア") == 0) {
			sorted.at(12) = *ite;
			//sorted.at(12).goal(43);
			//sorted.at(12).lost(55);
		} else if (ite->team().compare("レアル サラゴサ") == 0) {
			sorted.at(13) = *ite;
			//sorted.at(13).goal(46);
			//sorted.at(13).lost(64);
		} else if (ite->team().compare("スポルティング ヒホン") == 0) {
			sorted.at(14) = *ite;
			//sorted.at(14).goal(36);
			//sorted.at(14).lost(51);
		} else if (ite->team().compare("ラシン サンタンデール") == 0) {
			sorted.at(15) = *ite;
			//sorted.at(15).goal(42);
			//sorted.at(15).lost(59);
		} else if (ite->team().compare("マラガ") == 0) {
			sorted.at(16) = *ite;
			//sorted.at(16).goal(42);
			//sorted.at(16).lost(48);
		} else if (ite->team().compare("バジャドリー") == 0) {
			sorted.at(17) = *ite;
			//sorted.at(17).goal(37);
			//sorted.at(17).lost(62);
		} else if (ite->team().compare("テネリフェ") == 0) {
			sorted.at(18) = *ite;
			//sorted.at(18).goal(40);
			//sorted.at(18).lost(74);
		} else if (ite->team().compare("シェレス") == 0) {
			sorted.at(19) = *ite;
			//sorted.at(19).goal(38);
			//sorted.at(19).lost(66);
		} else {
			assert(0);
		}
	}   // for
}

void sortAsLigaEspanola2011(const std::vector<Team>& original, std::vector<Team>& sorted) throw() {
	sorted.resize(original.size());

	for (std::vector<Team>::const_iterator ite = original.begin(); ite != original.end(); ++ite) {
		if (ite->team().compare("アルメリア") == 0) {
			sorted.at(18) = *ite;
		} else if (ite->team().compare("アスレティック ビルバオ") == 0) {
			sorted.at(6) = *ite;
		} else if (ite->team().compare("バルセロナ") == 0) {
			sorted.at(1) = *ite;
		} else if (ite->team().compare("エスパニョール") == 0) {
			sorted.at(8) = *ite;
		} else if (ite->team().compare("ヘタフェ") == 0) {
			sorted.at(10) = *ite;
		} else if (ite->team().compare("スポルティング ヒホン") == 0) {
			sorted.at(15) = *ite;
		} else if (ite->team().compare("アトレティコ マドリー") == 0) {
			sorted.at(5) = *ite;
		} else if (ite->team().compare("レアル マドリー") == 0) {
			sorted.at(2) = *ite;
		} else if (ite->team().compare("マラガ") == 0) {
			sorted.at(7) = *ite;
		} else if (ite->team().compare("マジョルカ") == 0) {
			sorted.at(14) = *ite;
		} else if (ite->team().compare("オサスナ") == 0) {
			sorted.at(11) = *ite;
		} else if (ite->team().compare("ラシン サンタンデール") == 0) {
			sorted.at(13) = *ite;
		} else if (ite->team().compare("セビージャ") == 0) {
			sorted.at(4) = *ite;
		} else if (ite->team().compare("バレンシア") == 0) {
			sorted.at(0) = *ite;
		} else if (ite->team().compare("ビジャレアル") == 0) {
			sorted.at(3) = *ite;
		} else if (ite->team().compare("レアル サラゴサ") == 0) {
			sorted.at(19) = *ite;
		} else {
			//assert(0);
		}
	}   // for
}

void sortAsPremierLeague2010(std::vector<Team>& original, std::vector<Team>& sorted) throw() {
	sorted.swap(original);

//	for (std::vector<Team>::iterator ite = original.begin(); ite != original.end(); ++ite) {
//		if (ite->team().compare("アルメリア") == 0) {
//			sorted.at(12) = *ite;
//		} else if (ite->team().compare("アスレティック ビルバオ") == 0) {
//			sorted.at(7) = *ite;
//		} else if (ite->team().compare("バルセロナ") == 0) {
//			sorted.at(0) = *ite;
//		} else if (ite->team().compare("デポルティーボ ラ コルーニャ") == 0) {
//			sorted.at(9) = *ite;
//		} else if (ite->team().compare("エスパニョール") == 0) {
//			sorted.at(10) = *ite;
//		} else if (ite->team().compare("ヘタフェ") == 0) {
//			sorted.at(5) = *ite;
//		} else if (ite->team().compare("スポルティング ヒホン") == 0) {
//			sorted.at(14) = *ite;
//		} else if (ite->team().compare("アトレティコ マドリー") == 0) {
//			sorted.at(8) = *ite;
//		} else if (ite->team().compare("レアル マドリー") == 0) {
//			sorted.at(1) = *ite;
//		} else if (ite->team().compare("マラガ") == 0) {
//			sorted.at(16) = *ite;
//		} else if (ite->team().compare("マジョルカ") == 0) {
//			sorted.at(4) = *ite;
//		} else if (ite->team().compare("オサスナ") == 0) {
//			sorted.at(11) = *ite;
//		} else if (ite->team().compare("ラシン サンタンデール") == 0) {
//			sorted.at(15) = *ite;
//		} else if (ite->team().compare("セビージャ") == 0) {
//			sorted.at(3) = *ite;
//		} else if (ite->team().compare("テネリフェ") == 0) {
//			sorted.at(18) = *ite;
//		} else if (ite->team().compare("バレンシア") == 0) {
//			sorted.at(2) = *ite;
//		} else if (ite->team().compare("バジャドリー") == 0) {
//			sorted.at(17) = *ite;
//		} else if (ite->team().compare("ビジャレアル") == 0) {
//			sorted.at(6) = *ite;
//		} else if (ite->team().compare("シェレス") == 0) {
//			sorted.at(19) = *ite;
//		} else if (ite->team().compare("レアル サラゴサ") == 0) {
//			sorted.at(13) = *ite;
//		} else {
//			assert(0);
//		}
//	}   // for
}


/*============================================================================
	ランクを求める
	
	スキルによる能力上昇の前
 ============================================================================*/
static unsigned char playerParamGetRankByParam( int position, unsigned char *param)
{
	static struct {
		unsigned char	paramRate[DISP_PARAM_TYPE_MAX];
		unsigned char	kijun[4];
	} position_table[13] = {
		{{	0,	35,	2,	6,	19,	1,	37,},	{	88,	84,	79,	75,},},	// PR_GK,
		{{	6,	39,	15,	11,	18,	11,	0,},	{	84,	81,	76,	73,},},	// PR_LIB,	// なし
		{{	6,	39,	15,	11,	18,	11,	0,},	{	84,	81,	76,	73,},},	// PR_SW,
		{{	7,	43,	13,	11,	16,	10,	0,},	{	84,	81,	76,	73,},},	// PR_CB,
		{{	15,	15,	19,	21,	12,	18,	0,},	{	81,	78,	75,	72,},},	// PR_SB,
		{{	14,	23,	18,	12,	14,	19,	0,},	{	80,	78,	75,	72,},},	// PR_DH,
		{{	16,	15,	19,	19,	13,	18,	0,},	{	80,	78,	75,	72,},},	// PR_WB,
		{{	17,	18,	21,	11,	13,	20,	0,},	{	83,	79,	75,	72,},},	// PR_CH,
		{{	20,	9,	17,	19,	13,	22,	0,},	{	81,	79,	75,	72,},},	// PR_SH,
		{{	24,	6,	15,	15,	13,	27,	0,},	{	84,	80,	78,	75,},},	// PR_OH,
		{{	23,	2,	15,	24,	12,	24,	0,},	{	85,	82,	78,	75,},},	// PR_WG,
		{{	29,	1,	15,	19,	13,	23,	0,},	{	86,	83,	79,	75,},},	// PR_ST,
		{{	35,	1,	14,	17,	16,	17,	0,},	{	85,	82,	79,	75,},},	// PR_CF,
	};
	int total,i;
	// 合計値
	for ( i = 0, total = 0; i < DISP_PARAM_TYPE_MAX; i++){
		total += param[i] * position_table[position].paramRate[i];
	}
	total = (total + 50)/ 100;

	if( total >= position_table[position].kijun[0]) return 5;
	if( total >= position_table[position].kijun[1]) return 4;
	if( total >= position_table[position].kijun[2]) return 3;
	if( total >= position_table[position].kijun[3]) return 2;
	return 1;
}


//! \brief ファイル読込み
//! \note   選手データの読込み
std::vector<Team> readParamFile(std::string fileName) throw() {

	//std::ifstream file("param_for_GameAlgorithm.csv");
	std::ifstream file(fileName.c_str());

	if (!file.is_open()) {
		so::out << "Couldn\'t open file!!!" << so::endl;
		assert(0);
	}

	std::multimap<std::string, DispParam> container;
	std::string line;

	// 最初の２行はいらない情報
	getline(file, line);
	getline(file, line);

	DispParam param;

	while (!file.eof()) {
		static int count = 1;
		getline(file, line);
		++count;

		if (line == "") {
			continue;
		}

		std::vector<std::string> paramList;
		paramList = boost::algorithm::split(paramList, line, boost::is_any_of(","));

		param.team(paramList.at(ParamList_team));
		param.name(paramList.at(ParamList_name));
		param.position(paramList.at(ParamList_position));
		param.side(getParam(ParamList_side));
		param.attack(AttackDispParam(getParam(ParamList_offence), getParam(ParamList_shotAcc), getParam(ParamList_shotTech)).get());
		param.defence(DefenceDispParam(getParam(ParamList_defence)).get());
		param.stamina(StaminaDispParam(getParam(ParamList_stamina)).get());
		param.speed(SpeedDispParam(getParam(ParamList_topSpeed), getParam(ParamList_acceralation), getParam(ParamList_aggility)).get());
		param.power(PowerDispParam(getParam(ParamList_bodyBarance), getParam(ParamList_shotPower)).get());
		param.pass(PassDispParam(getParam(ParamList_trap), getParam(ParamList_shortPassAcc), getParam(ParamList_longPassAcc)).get());
		param.dribble(DribbleDispParam(getParam(ParamList_trap), getParam(ParamList_dribbleSpeed), getParam(ParamList_dribbleAcc)).get());
		param.gkSkill(GkSkillDispParam(getParam(ParamList_gkSkill)).get());
		param.connection(getParam(ParamList_connection));
		param.injury(paramList.at(ParamList_injury));
		param.star(getParam(ParamList_star));

		setSkill(param, SkillCard_dribbler);
		setSkill(param, SkillCard_postPlay);
		setSkill(param, SkillCard_positioning);
		setSkill(param, SkillCard_popOut);
		setSkill(param, SkillCard_playMaker);
		setSkill(param, SkillCard_passer);
		setSkill(param, SkillCard_PKKicker);
		setSkill(param, SkillCard_1vs1Shoot);
		setSkill(param, SkillCard_longThrow);
		setSkill(param, SkillCard_directPlay);
		setSkill(param, SkillCard_manMark);
		setSkill(param, SkillCard_defenceLeader);
		setSkill(param, SkillCard_1vs1Keeper);
		setSkill(param, SkillCard_outside);
		setSkill(param, SkillCard_sidePlayer);
		setSkill(param, SkillCard_centerPlayer);
		setSkill(param, SkillCard_superSub);
		setSkill(param, SkillCard_sliding);
		setSkill(param, SkillCard_covering);

		container.insert(std::pair<std::string, DispParam>(param.team(), param));
		param.clear();
	}

	std::vector<Team> temp(1);
	std::multimap<std::string, DispParam>::iterator begin = container.begin();
	std::multimap<std::string, DispParam>::iterator end = container.end();

	std::string teamName = begin->second.team();

	try {
		for (std::multimap<std::string, DispParam>::iterator ite = begin; ite != end; ++ite) {
			if (teamName.compare(ite->second.team()) != 0) {
				temp.push_back(Team());
				teamName = ite->second.team();
			}
			temp.back().add(ite->second);
		}
	} catch(...) {
		assert(0);
	}

	for (std::vector<Team>::iterator ite = temp.begin(); ite != temp.end(); ++ite) {
		ite->reset();
	}

	std::vector<Team> result;

	if (fileName.compare("Liga_Espanola.csv") == 0) {
		sortAsLigaEspanola2010(temp, result);
		//sortAsLigaEspanola2011(temp, result);
	} else if (fileName.compare("Premier_League.csv") == 0) {
		sortAsPremierLeague2010(temp, result);
	} else if (fileName.compare("Serie_A.csv") == 0) {
		sortAsPremierLeague2010(temp, result);
	} else if (fileName.compare("League_1.csv") == 0) {
		sortAsPremierLeague2010(temp, result);
	} else if (fileName.compare("Eledivisie.csv") == 0) {
		sortAsPremierLeague2010(temp, result);
	}

	eraseByFunctor(result, FindTeamName(""));
	return result;
}



/**----------------------------------------------------
 * @brief 引数で指定されたデータに関してランダムな数値を作成する
 * @param[in]   position_   作成中の選手のポジション
 * @param[in]   paraName_   データが欲しいパラメータの名前
 *---------------------------------------------------*/
float gausianRandom(float average, float sigma) throw()
{
	static float n2 = 0.0;
	static bool n2_cached = false;

	if (!n2_cached) {
		double x, y, r;
		do {
			x = 2.0*rand()/RAND_MAX - 1;
			y = 2.0*rand()/RAND_MAX - 1;
 
			r = x*x + y*y;
		} while (r == 0.0 || r > 1.0);
 
		{
			float d = sqrt(-2.0*log(r)/r);
			float n1 = x*d;
			n2 = y*d;
 
			float result = n1*sigma + average;
 
			n2_cached = 1;
			return result;
		}
	} else {
		n2_cached = 0;
		return n2*sigma + average;
	}
}

//{
//	// ランダムな数字を２つ作成
//	int random = rand()%100000;
//	float x = static_cast<float>(random)/100000.0f;
//	random = rand()%100000;
//	float y = static_cast<float>(random)/100000.0f;
//
//	// ガウス分布に応じた確立でランダムな数を１つ作成
//	double result = .0;
//	result = sqrt((-2 * log(y))) * (cos(2 * M_PI * x));
//
//	// 平均値と分散を使ってランダム値を計算
//	float returnData = static_cast<float>((result * sigma) + average);
//
//	return returnData;
//}


#endif

