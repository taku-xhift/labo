

#include <iostream>

enum PositionID
{
	POSID_GK,
	POSID_LIB,
	POSID_SW,
	POSID_CB,
	POSID_SB,
	POSID_DH,
	POSID_WB,
	POSID_CH,
	POSID_SH,
	POSID_OH,
	POSID_WG,
	POSID_ST,
	POSID_CF,
	POSID_MAX
};


enum ParameterName
{
	PARAMETERNAME_OFFENCE,
	PARAMETERNAME_DEFENCE,
	PARAMETERNAME_STAMINA,
	PARAMETERNAME_SPEED,
	PARAMETERNAME_POWER,
	PARAMETERNAME_DRIBBLE,
	PARAMETERNAME_PASS,
	PARAMETERNAME_GK_SKILL,
	PARAMETERNAME_TYPEMAX,
};



int paramRateArray[POSID_MAX][PARAMETERNAME_TYPEMAX]  = {
	{	0,	38,	2,	7,	13,	0,	1,	39,},// POSID_GK,
	{	6,	39,	15,	11,	18,	0,	11,	0,},// POSID_LIB,
	{	6,	39,	15,	11,	18,	0,	11,	0,},// POSID_SW,
	{	6,	50,	12,	10,	15,	0,	7,	0,},// POSID_CB,
	{	15,	13,	20,	19,	12,12,	9,	0,},// POSID_SB,
	{	16,	19,	20,	12,	14,	5,	14,	0,},// POSID_DH,
	{	16,	12,	20,	17,	12,	12,	11,	0,},// POSID_WB,
	{	17,	18,	20,	11,	11,	9,	14,	0,},// POSID_CH,
	{	19,	9,	17,	19,	12,	12,	12,	0,},// POSID_SH,
	{	23,	5,	12,	13,	13,	13,	21,	0,},// POSID_OH,
	{	25,	2,	13,	23,	12,	13,	12,	0,},// POSID_WG,
	{	33,	1,	12,	17,	11,	12,	14,	0,},// POSID_ST,
	{	46,	0,	9,	16,	13,	10,	6,	0,}// POSID_CF,
};
int baseLineArray[POSID_MAX][4]  = {
	{	8800,	8300,	7800,	7550,},// POSID_GK,
	{	8400,	8100,	7600,	7300,},// POSID_LIB,
	{	8400,	7900,	7500,	7300,},// POSID_SW,
	{	8400,	7900,	7500,	7300,},// POSID_CB,
	{	8000,	7650,	7400,	7150,},// POSID_SB,
	{	8000,	7650,	7450,	7150,},// POSID_DH,
	{	7960,	7650,	7400,	7100,},// POSID_WB,
	{	8050,	7650,	7400,	7200,},// POSID_CH,
	{	8100,	7800,	7500,	7250,},// POSID_SH,
	{	8250,	7850,	7650,	7400,},// POSID_OH,
	{	8500,	8050,	7800,	7500,},// POSID_WG,
	{	8500,	8100,	7800,	7500,},// POSID_ST,
	{	8500,	8100,	7850,	7500,},// POSID_CF,
};


struct Parameter
{
public:

	int offence;
	int deffence;
	int stamina;
	int speed;
	int power;
	int dribble;
	int pass;
	int GK_skill;
	PositionID position;

	Parameter()
		: offence(0)
		, deffence(0)
		, stamina(0)
		, speed(0)
		, power(0)
		, dribble(0)
		, pass(0)
		, GK_skill(0)
		, position(POSID_MAX)
	{
	}
};


int getBase(Parameter param_)
{
	int returnValue = 0;

	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_OFFENCE];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_DEFENCE];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_STAMINA];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_SPEED];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_POWER];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_DRIBBLE];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_PASS];
	returnValue += param_.offence * paramRateArray[param_.position][PARAMETERNAME_GK_SKILL];

	std::cout << "ƒx[ƒX" << returnValue << std::endl;

	return returnValue;
}

int getRank(int base_, PositionID position_)
{
	int returnValue = 0;

	if (base_ > baseLineArray[static_cast<int>(position_)][0]) {
		returnValue = 5;
	} else if (base_ > baseLineArray[static_cast<int>(position_)][1]) {
		returnValue = 4;
	} else if (base_ > baseLineArray[static_cast<int>(position_)][2]) {
		returnValue = 3;
	} else if (base_ > baseLineArray[static_cast<int>(position_)][3]) {
		returnValue = 2;
	} else {
		returnValue = 1;
	}

	return returnValue;
}

int main()
{
	Parameter parameter;
	parameter.offence = 69;
	parameter.deffence = 75;
	parameter.stamina = 90;
	parameter.speed = 69;
	parameter.power = 45;
	parameter.dribble = 88;
	parameter.pass = 54;
	parameter.GK_skill = 50;
	parameter.position = POSID_CF;

	std::cout << "Rank is " << getRank(getBase(parameter), parameter.position) << std::endl;

	return 0;
}


