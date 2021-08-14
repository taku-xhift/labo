
#ifndef DEFINE_HPP_INCLUDED
#define DEFINE_HPP_INCLUDED

#pragma warning(disable:4996)
#pragma warning(disable:4290)

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


#define getParam(ParamList) ::boost::lexical_cast<float>(paramList.at(ParamList))
#define setSkill(DispParam, SkillCard) DispParam.skill(SkillCard, converterFromStarToBoolean(paramList.at(SkillCard))
#define ExceptionMessage(message_)     std::string("Exception is thrown!!\nmessage: " + std::string(message_) + "\nfile: " + ::boost::lexical_cast<std::string>(__FILE__) + "\nline: " + ::boost::lexical_cast<std::string>(__LINE__) + "\nfunction: " + ::boost::lexical_cast<std::string>(__FUNCTION__) + "\n").c_str()

//====  eraseByFunctor  =============================================
//! \brief �����t�@���N�^���w�肵�� true �̂��̂���������
//! \param[in]  container_      �R���e�i
//! \param[in]  functor_        ��������t�@���N�^
//! \return     �������I������R���e�i�̍ŏI�v�f�̎����w���C�e���[�^
template<typename ContainerType, typename Functor>
typename ContainerType::iterator eraseByFunctor(ContainerType& container_, Functor& functor_) throw() {
	return container_.erase(std::remove_if(container_.begin(), container_.end(), functor_), container_.end());
}
namespace {
	static std::string fileName = "";
	const std::string LigaData = "Liga_Espanola.csv";
	const std::string PremierData = "Premier_League.csv";
	const std::string SerieAData = "Serie_A.csv";
	const std::string League1Data = "League_1.csv";
	const std::string EledivisieData = "Eledivisie.csv";
}


enum PosList {
	PosList_GK,
	PosList_CB,
	PosList_SB,
	PosList_DMF,
	PosList_SMF,
	PosList_ST,
	PosList_CF,
	PosList_CMF,
	PosList_OMF,
	PosList_SW,
	PosList_WG,
	PosList_WB,
	PosList_max,
};

enum DISP_PARAM_TYPE
{
	DISP_PARAM_OFFENSE,
	DISP_PARAM_DEFENCE,
	DISP_PARAM_STAMINA,
	DISP_PARAM_SPEED,
	DISP_PARAM_POWER,
	DISP_PARAM_TECHNIQUE,
	DISP_PARAM_GK_SKILL,
	DISP_PARAM_TYPE_MAX
};

enum SkillCard {
	SkillCard_dribbler,
	SkillCard_postPlay,
	SkillCard_positioning,
	SkillCard_popOut,
	SkillCard_playMaker,//�i�ߓ�
	SkillCard_passer,
	SkillCard_PKKicker,
	SkillCard_1vs1Shoot,
	SkillCard_longThrow,
	SkillCard_directPlay,
	SkillCard_manMark,
	SkillCard_defenceLeader,// DF���C������
	SkillCard_1vs1Keeper,
	SkillCard_outside,
	SkillCard_sidePlayer,
	SkillCard_centerPlayer,
	SkillCard_superSub,
	SkillCard_sliding,
	SkillCard_covering,
	SkillCard_max,
};

// �ǂݍ��ރt�@�C���̃f�[�^�̕��я�
enum ParamList {
	ParamList_team,
	ParamList_name,
	ParamList_eName,
	ParamList_position,
	ParamList_side,
	ParamList_offence,
	ParamList_defence,
	ParamList_bodyBarance,
	ParamList_stamina,
	ParamList_topSpeed,
	ParamList_acceralation,
	ParamList_responce,
	ParamList_dribbleAcc,
	ParamList_dribbleSpeed,
	ParamList_shortPassAcc,
	ParamList_shortPassSpeed,
	ParamList_longPassAcc,
	ParamList_longPassSpeed,
	ParamList_shotPower,
	ParamList_shotAcc,
	ParamList_shotTech,
	ParamList_jump,
	ParamList_head,
	ParamList_trap,
	ParamList_technique,
	ParamList_curb,
	ParamList_positive,
	ParamList_mentality,
	ParamList_condition,
	ParamList_freeKick,
	ParamList_connection,
	ParamList_aggility,
	ParamList_gkSkill,
	// �ȉ��X�L��
	ParamList_dribbler,
	ParamList_postPlay,
	ParamList_positioning,
	ParamList_popOut,
	ParamList_playMaker,//�i�ߓ�
	ParamList_passer,
	ParamList_PKKicker,
	ParamList_1vs1Shoot,
	ParamList_longThrow,
	ParamList_directPlay,
	ParamList_manMark,
	ParamList_defenceLeader,// DF���C������
	ParamList_1vs1Keeper,
	ParamList_outside,
	ParamList_sidePlayer,
	ParamList_centerPlayer,
	ParamList_superSub,
	ParamList_sliding,
	ParamList_covering,
	// �ȉ�����
	ParamList_injury,
	ParamList_star,
	ParamList_max,
};


class ExceptBase
	: public std::exception
{
public:

	ExceptBase(std::string message = "class ExceptBase") throw()
		: message_(message) {}

	virtual const char* what() const throw() {
		return this->message_.c_str();
	}

private:
	std::string message_;
};


class DevideByZero
	: public ExceptBase
{
public:

	DevideByZero(std::string message = "class DevideByZero") throw()
		: ExceptBase(message)
	{
	}
};

class ConvertError
	: public ExceptBase
{
public:

	ConvertError(std::string message = "class ConvertError") throw()
		: ExceptBase(message)
	{
	}
};


#endif

