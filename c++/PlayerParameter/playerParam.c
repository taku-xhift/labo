/*****************************************************************************

 playerParam.c

 Y.Saito, usr04538
 2007/1/17

 (c) Copyright 2002 KONAMI TYO All Rights Reserved

 *****************************************************************************/

/**** include files **********************************************************/
#include	"playerParam.h"
#include	"playerMiiData.h"

#include	"weCommonMath.h"

#include	"deDataPlayer.h"
#include	"deDataPlayerMacro.h"
#include	"dataAccessPlayer.h"
#include	"parameter.h"

#include	"weString.h"
#include	"weStrDataWcm2W.h"

#include	"plFaceData.h"

#include	"player_id.h"

#include	"crGlobal.h"	// これはずしたい・・・
#include	"mii.cnf"

#include	"league.cnf"
#include	"weOverlay.h"
#include	"weOverlayArea.h"
#include	"overlayTable.h"
#include	"lc_exec.h"
#include	"lc_member_proto.h"

/**** module defines *********************************************************/

/**** module macro functions *************************************************/

/**** module enumerations ****************************************************/

/**** module typedefs ********************************************************/
typedef struct{
	weFloat	importance;
	weFloat	param;
} PLAYER_PARAM_MAKE_AVERAGE_W;

/**** module external variables **********************************************/

/**** module internal variables **********************************************/
// ランクを求める際のテーブル
static struct {
	weUchar		paramRate[DISP_PARAM_TYPE_MAX];
	weUshort	kijun[4];
} rank_position_table[PR_MAX] = {
	{{	0,	38,	2,	7,	13,	0,	1,	39,},	{	8800,	8300,	7800,	7550,},},// PR_GK,
	{{	6,	39,	15,	11,	18,	0,	11,	0,},	{	8400,	8100,	7600,	7300,},},// PR_LIB,	// なし
	{{	6,	39,	15,	11,	18,	0,	11,	0,},	{	8400,	7900,	7500,	7300,},},// PR_SW,	// なし
	{{	6,	50,	12,	10,	15,	0,	7,	0,},	{	8400,	7900,	7500,	7300,},},// PR_CB,
	{{	15,	13,	20,	19,	12,12,	9,	0,},	{	8000,	7650,	7400,	7150,},},// PR_SB,
	{{	16,	19,	20,	12,	14,	5,	14,	0,},	{	8000,	7650,	7450,	7150,},},// PR_DH,
	{{	16,	12,	20,	17,	12,	12,	11,	0,},	{	7960,	7650,	7400,	7100,},},// PR_WB,
	{{	17,	18,	20,	11,	11,	9,	14,	0,},	{	8050,	7650,	7400,	7200,},},// PR_CH,
	{{	19,	9,	17,	19,	12,	12,	12,	0,},	{	8100,	7800,	7500,	7250,},},// PR_SH,
	{{	23,	5,	12,	13,	13,	13,	21,	0,},	{	8250,	7850,	7650,	7400,},},// PR_OH,
	{{	25,	2,	13,	23,	12,	13,	12,	0,},	{	8500,	8050,	7800,	7500,},},// PR_WG,
	{{	33,	1,	12,	17,	11,	12,	14,	0,},	{	8500,	8100,	7800,	7500,},},// PR_ST,
	{{	46,	0,	9,	16,	13,	10,	6,	0,},	{	8500,	8100,	7850,	7500,},},// PR_CF,
};
#define RANK_BASE_SUV_PHY95		100
#define RANK_BASE_SUV_TEC90		50
#define RANK_BASE_SUV_TEC95		150
#define RANK_BASE_SUV_HIGH		100

/**** module function prototypes *********************************************/
static PLAYER_ABILITY_PERMANENT *playerParamGetPlayerParaAbility( WE_PID_T pid);
static weInt playerParamGetPlayerAge( WE_PID_T pid);
static void playerParamMakeAverageInit( PLAYER_PARAM_MAKE_AVERAGE_W *pw);
static void playerParamMakeAverageAdd( PLAYER_PARAM_MAKE_AVERAGE_W *pw, weFloat importance, weFloat param);
static weUchar playerParamMakeAverageGet( PLAYER_PARAM_MAKE_AVERAGE_W *pw, weFloat base, weFloat add);
static weUchar playerParamGetOffense( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetDefence( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetStamina( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetSpeed( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetPower( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetDribble( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetPass( PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetGkSkill( PLAYER_ABILITY_PERMANENT *ability);
static void playerParamSetRankBase( PLAYER_DISP_PARAM_WORK *param, PLAYER_ABILITY_PERMANENT *ability);
static weUchar playerParamGetRankByParam( weInt position, weInt rank_base);
static weUchar playerParamGetBestRank( weUchar *rank_pos);
static void playerParamAddParamUp( SKILL_EXP_WORK *skill_exp, weUchar *param);
static void playerParamMakePositionBlock( PLAYER_DISP_PARAM_POS_BLOCK *posBlock, PLAYER_ABILITY_PERMANENT *ability, weBool all_arounder, weBool flying_man);
static weInt playerParamGetAptitudePart( weInt position, PLAYER_ABILITY_PERMANENT *ability);


/**** module others **********************************************************/



/*============================================================================
	表示用のパラメータを作る
	引数：	(I/O)ooo	:
			(I/O)ooo	:
	返値：	ooo	:
	備考：
 ============================================================================*/
void playerParamMakeDispParam( WE_PID_T pid, PLAYER_DISP_PARAM_WORK *param)
{
	playerParamMakeDispParamBySkill( pid, NULL, param);
}
void playerParamMakeDispParamBySkill( WE_PID_T pid, SKILL_EXP_WORK *setSkillExp, PLAYER_DISP_PARAM_WORK *param)
{
	PLAYER_ALL_DATA		*all,all_w;
	PLAYER_ABILITY_PERMANENT		*ability;
	SKILL_EXP_WORK		powSkillExp[PLAYER_SKILL_MAX];	// パワーアップに使うスキルリスト
	SKILL_EXP_WORK		miiSkillExp[PLAYER_SKILL_MAX];	// Miiようにセットするスキル
	weInt	i;
	weInt	age;
	WE_PID_T real_pid;

	// まずクリア
	memset( param, 0, sizeof( PLAYER_DISP_PARAM_WORK));

	// 元の能力値を取得
#if WII_MII == 1
	if( PID_MII_TOP <= pid && pid <= PID_MII_END){
		// もともとMii選手が登録されている
		MII_CREATE_ID	create_id;
		all = &all_w;
		setSkillExp = miiSkillExp;
		// Miiを特定する
		playerMiiSetCreateIDByPID( &create_id, pid);
		real_pid = pid;
		// パラメータ作成
		playerMiiSetParamByMiiCreateID( all, &create_id);
		ability = &all->para.ability;
		// スキルも取得
		playerMiiSetSkillByMiiCreateID( miiSkillExp, &create_id);
	} else {
		real_pid = GetRealPlayerID( pid);
		ability = playerParamGetPlayerParaAbility(pid);
		all = GetPlayerAllDataAddress2_IDD( pid, OFF);
	}
#else
	real_pid = GetRealPlayerID( pid);
	ability = playerParamGetPlayerParaAbility(pid);
	all = GetPlayerAllDataAddress2_IDD( pid, OFF);
#endif
	
	// 基本データ
	param->high = all->para.appear.high + MIN_HEIGHT;
	age = playerParamGetPlayerAge( pid);
	param->age  = age + MIN_AGE;
	param->foot = ability->lefty;
#if WII_MII == 1
	param->mii  = all->para.appear.mii;
#endif	//	WII_MII == 1

	// ポジションのセット
	param->position = ability->position;

	if( 1  ){
		playerParamMakeAbility( ability, param);
		// ランクのベース値を求める
		playerParamSetRankBase( param, ability);

		// ランクを求める
		// スキルによる能力上昇の前
#if 0//WII_MII == 1
		if( all->para.appear.mii &&
			all->para.appear.face_type + PL_FACE_DATA_MII_START == PL_FACE_DATA_MII_OFFICIAL &&
			!( PID_CR_YOUTH_TOP <= real_pid && real_pid <= PID_CR_YOUTH_END)){
			// ユーザーのMiiは固定
			// ただし、Mii育成選手はのぞく
			param->rank = 3;
		} else
#endif	//	WII_MII == 1
		{
			param->rank = playerParamGetBestRank( param->rank_pos);
		}
	}

	// スキル
	if(setSkillExp != NULL){
		// スキルがセットされていれば、それでよし
		for( i = 0; i < PLAYER_SKILL_MAX; i++){
			powSkillExp[i] = setSkillExp[i];
			param->skillList[i]     = powSkillExp[i].skill;
			param->skillCompleteRate[i] = playerSkillGetCompleteRate(&powSkillExp[i]);
		}
	} else {
		// スキルを取得
		playerSkillMakeSkillExp( powSkillExp, pid);
		for( i = 0; i < PLAYER_SKILL_MAX; i++){
			param->skillList[i]     = powSkillExp[i].skill;
			param->skillCompleteRate[i] = playerSkillGetCompleteRate(&powSkillExp[i]);
		}
	}

	// スキルによる能力値の上昇
	playerParamAddParamUp( powSkillExp, param->param);
	
	// ポジション表の作成
	playerParamMakePositionBlock(	&param->posBlock,
									ability,
									playerSkillExpCheck( powSkillExp, SKILL_ALL_AROUNDER),
									playerSkillExpCheck( powSkillExp, SKILL_FLYING_MAN));
	// 全パラメータ保存
	param->all = *all;
	param->all.para.ability = *ability; // パラメータ上書き
	param->all.para.appear.age = age;	// 年齢修正
	// スキルによるパラメータアップ
	playerSkillAddParamSkillExp( powSkillExp, &param->all.para.ability, FALSE);
}

/*============================================================================
	パラメータ取得
 ============================================================================*/
static PLAYER_ABILITY_PERMANENT *playerParamGetPlayerParaAbility( WE_PID_T pid)
{
	PLAYER_ABILITY_PERMANENT		*ability;
	weInt				side,no;

#if LEAGUE_USE
	if (LC_IsMasterLeague() ){
		if ((weOverlayGetOverlayID(OVL_AREA_0) == OVL_ID_LEAGUEWORK) &&  LC_OVERLAY_MODE_NONE!=LC_OverlayModeCheck()) {
			// 通常
			ability = &LC_GetParaAddress_ID(pid)->ability;
			return ability;
		} else {
			// 試合中
			// ML中は能力スキルとかもつかないのでそのままの奴を
			for(side=0;side<GAME_TEAM_SUU;side++){
				for(no=0;no<MEMBER_SUU_MAX;no++){
					if( pid == MEMBER_ID(side,no)){
						// 同じ選手がいたら
						ability = (PLAYER_ABILITY_PERMANENT*)(&MEMBER_PARAMETER_BK(side,no));
						return ability;
					}
				}
			}
			
		}
	}
	// 条件に当てはまらない場合は普通のパラメータ取得
	ability = &GetParaAddress_ID(pid)->ability;
#else
	ability = &GetParaAddress_ID(pid)->ability;
#endif

	return ability;
}
/*============================================================================
	年齢取得
 ============================================================================*/
static weInt playerParamGetPlayerAge( WE_PID_T pid)
{
	weInt				age;
	weInt				side,no;

#if LEAGUE_USE
	if (LC_IsMasterLeague() ){
		if ((weOverlayGetOverlayID(OVL_AREA_0) == OVL_ID_LEAGUEWORK) &&  LC_OVERLAY_MODE_NONE!=LC_OverlayModeCheck()) {
			// 通常
			age = LC_GetParaAddress_ID(pid)->appear.age;
			return age;
		} else {
			// 試合中
			// ML中は能力スキルとかもつかないのでそのままの奴を
			for(side=0;side<GAME_TEAM_SUU;side++){
				for(no=0;no<MEMBER_SUU_MAX;no++){
					if( pid == MEMBER_ID(side,no)){
						// 同じ選手がいたら
						age = MEMBER_PARAMETER(side,no).age;
						return age;
					}
				}
			}
			
		}
	}
	// 条件に当てはまらない場合は普通の年齢取得
	age = GetParaAddress_ID(pid)->appear.age;
#else
	age = GetParaAddress_ID(pid)->appear.age;
#endif

	return age;
}

/*============================================================================
	重みつきの平均値を求める
 ============================================================================*/
void playerParamMakeAbility( PLAYER_ABILITY_PERMANENT *ability, PLAYER_DISP_PARAM_WORK *param)
{
	// 能力値を作成
	param->param[DISP_PARAM_OFFENSE]	= playerParamGetOffense(   ability);
	param->param[DISP_PARAM_DEFENCE]	= playerParamGetDefence(   ability);
	param->param[DISP_PARAM_STAMINA]	= playerParamGetStamina(   ability);
	param->param[DISP_PARAM_SPEED]		= playerParamGetSpeed(     ability);
	param->param[DISP_PARAM_POWER]		= playerParamGetPower(     ability);
	param->param[DISP_PARAM_PASS]		= playerParamGetPass(      ability);
	param->param[DISP_PARAM_DRIBBLE]	= playerParamGetDribble(   ability);
	param->param[DISP_PARAM_GK_SKILL]	= playerParamGetGkSkill(   ability);
}

/*============================================================================
	重みつきの平均値を求める
 ============================================================================*/
static void playerParamMakeAverageInit( PLAYER_PARAM_MAKE_AVERAGE_W *pw)
{
	pw->importance = 0;
	pw->param = 0;
}
static void playerParamMakeAverageAdd( PLAYER_PARAM_MAKE_AVERAGE_W *pw, weFloat importance, weFloat param)
{
	pw->importance	+= importance;
	pw->param		+= importance * param;
}
static weUchar playerParamMakeAverageGet( PLAYER_PARAM_MAKE_AVERAGE_W *pw, weFloat base, weFloat add)
{
	weFloat	point;
	weFloat	importance = 0;
	weFloat	param = 0;

	importance = pw->importance;
	param      = pw->param;

	point = (param / importance) * base + add;
	point = WE_MIN( point, 99.0f);
	return (weUchar)(point);
}

/*----------------------------------------------------------------------------
	攻撃力
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetOffense( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	2,	ability->offence);
	playerParamMakeAverageAdd( pw,	1,	ability->shotacc);
	playerParamMakeAverageAdd( pw,	1,	ability->shottech);

	para = playerParamMakeAverageGet(pw,1.00,1.5f);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	守備力
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetDefence( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	1,	ability->defence);

	para = playerParamMakeAverageGet(pw,1,0);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	スタミナ
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetStamina( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	1,	ability->stamina);

	para = playerParamMakeAverageGet(pw,1,0);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	スピード
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetSpeed( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
	// レスポンスはスピードのない人に付けるイメージがある
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	2,	ability->dash);
	playerParamMakeAverageAdd( pw,	1,	ability->kasoku);
	playerParamMakeAverageAdd( pw,	1,	ability->agility);

	para = playerParamMakeAverageGet(pw,0.97f,+4.0f);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	パワー
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetPower( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
	// パワーがある人はジャンプしなくても大丈夫なので、ジャンプ力がなかったりする
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	2,	ability->atari);
	playerParamMakeAverageAdd( pw,	1,	ability->shotpower);

	para = playerParamMakeAverageGet(pw,1.01f,0);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	ドリブル
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetDribble( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
	// 基本的なテクニックと、ドリブル精度、ドリブルスピード
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	1,	ability->trap);
	playerParamMakeAverageAdd( pw,	2,	ability->dribble);
	playerParamMakeAverageAdd( pw,	1,	ability->dribblespeed);

	para = playerParamMakeAverageGet(pw, 0.98f, 0.0f);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	パス
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetPass( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
	// 2種類のパスタイプと基本的なテクニックの総合値
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	1,	ability->trap);
	playerParamMakeAverageAdd( pw,	2,	ability->passacc);
	playerParamMakeAverageAdd( pw,	2,	ability->longacc);

	para = playerParamMakeAverageGet(pw, 1.01f, 0.0f);
	para = WE_MAX( para, 30);
	return para;
}
/*----------------------------------------------------------------------------
	GK能力
 ----------------------------------------------------------------------------*/
static weUchar playerParamGetGkSkill( PLAYER_ABILITY_PERMANENT *ability)
{
	PLAYER_PARAM_MAKE_AVERAGE_W ppm,*pw = &ppm;
	weUchar	para;

	playerParamMakeAverageInit( pw);
								/* 重み パラメータ */
	playerParamMakeAverageAdd( pw,	1,	ability->gk_skill);

	para = playerParamMakeAverageGet(pw,1,0);
	para = WE_MAX( para, 30);
	return para;
}


/*============================================================================
	ランクのベース値を求める
	
	スキルによる能力上昇の前
 ============================================================================*/
static void playerParamSetRankBase( PLAYER_DISP_PARAM_WORK *param, PLAYER_ABILITY_PERMANENT *ability)
{
	weInt	total,i;
	weInt	position;
	weBool	aptitude;

	for( position = 0; position < PR_MAX; position++){
		aptitude = FALSE;
		switch( position){
		case PR_GK: if( ability->gk ) aptitude = TRUE; break;
		case PR_CB: if( ability->cb ) aptitude = TRUE; break;
		case PR_SB: if( ability->sb ) aptitude = TRUE; break;
		case PR_DH: if( ability->dh ) aptitude = TRUE; break;
		case PR_WB: if( ability->wb ) aptitude = TRUE; break;
		case PR_CH: if( ability->ch ) aptitude = TRUE; break;
		case PR_SH: if( ability->sh ) aptitude = TRUE; break;
		case PR_OH: if( ability->oh ) aptitude = TRUE; break;
		case PR_WG: if( ability->wg ) aptitude = TRUE; break;
		case PR_ST: if( ability->st ) aptitude = TRUE; break;
		case PR_CF: if( ability->cf ) aptitude = TRUE; break;
		}
		if( !aptitude){
			// 適性がない場合は飛ばす
			param->rank_base[position] = 0;
			param->rank_pos[ position] = 0;
			continue;
		}
		// 合計値
		for ( i = 0, total = 0; i < DISP_PARAM_TYPE_MAX; i++){
			total += param->param[i] * rank_position_table[position].paramRate[i];
		}
		// サービスポイント
		// フィジカル系
		if( param->param[DISP_PARAM_STAMINA] >= 95) total += RANK_BASE_SUV_PHY95;
		if( param->param[DISP_PARAM_SPEED  ] >= 95) total += RANK_BASE_SUV_PHY95;
		if( param->param[DISP_PARAM_POWER  ] >= 95) total += RANK_BASE_SUV_PHY95;

		// テクニック系
		if(      param->param[DISP_PARAM_DRIBBLE] >= 95) total += RANK_BASE_SUV_TEC95;
		else if( param->param[DISP_PARAM_DRIBBLE] >= 90) total += RANK_BASE_SUV_TEC90;
		if(      param->param[DISP_PARAM_PASS   ] >= 95) total += RANK_BASE_SUV_TEC95;
		else if( param->param[DISP_PARAM_PASS   ] >= 90) total += RANK_BASE_SUV_TEC90;
		// 身長
		if( param->high >= 190) total += RANK_BASE_SUV_HIGH;
		param->rank_base[position] = total;
		param->rank_pos[ position] = playerParamGetRankByParam( position, total);
	}
}


/*============================================================================
	ランクを求める
	
	スキルによる能力上昇の前
 ============================================================================*/
static weUchar playerParamGetRankByParam( weInt position, weInt rank_base)
{
	if( rank_base >= rank_position_table[position].kijun[0]) return 5;
	if( rank_base >= rank_position_table[position].kijun[1]) return 4;
	if( rank_base >= rank_position_table[position].kijun[2]) return 3;
	if( rank_base >= rank_position_table[position].kijun[3]) return 2;
	return 1;
}

/*============================================================================
	ランクを求める
	
	スキルによる能力上昇の前
 ============================================================================*/
static weUchar playerParamGetBestRank( weUchar *rank_pos)
{
	weInt position;
	weInt max_rank = 1;
	for( position = 0; position < PR_MAX; position++){
		if( max_rank < rank_pos[position]){
			max_rank = rank_pos[position];
		}
	}
	return max_rank;
}


/*============================================================================
	スキルによる能力値の上昇
 ============================================================================*/
static void playerParamAddParamUp( SKILL_EXP_WORK *skill_exp, weUchar *param)
{
	weUchar	upList[DISP_PARAM_TYPE_MAX];
	weInt	i;
	// スキル関係でパラメータを足す場合、99は超えない
	#define SKILL_ADD_PARAM( mem, add)	\
				mem = WE_MIN( mem + add, 99)

	playerSkillGetParamUp( skill_exp, upList);

	for( i = 0; i < DISP_PARAM_TYPE_MAX; i++){
		SKILL_ADD_PARAM( param[i], upList[i]);
	}
}


/*============================================================================
	ポジション表の作成
 ============================================================================*/
static void playerParamMakePositionBlock( PLAYER_DISP_PARAM_POS_BLOCK *posBlock, PLAYER_ABILITY_PERMANENT *ability, weBool all_arounder, weBool flying_man)
{
	enum{
		PCB,
		PSB,
		PDH,
		PWB,
		PCH,
		PSH,
		POH,
		PWG,
		PST,
		PCF,
		// 特殊デファイン
		PDC,	// DMF or CMF
		POC,	// OMF or CMF
		Psb,	// SBの後ろ
		PWS,	// WG or ST
		PCW,	// CMF or WB
		PCS,	// CMF or SMF
		PCT,	// CF or ST

		PGK,	// GK
		PNO,	// なし

		POS_APT_MAX,
	};
	enum{
		SIDE_R,
		SIDE_L,
		SIDE_B,	// 両方
		SIDE_MAX,
	};
	static weUchar	positionBlockTable[DISP_PARAM_POS_CUT_E][DISP_PARAM_POS_CUT_S] = {
		{ PNO, PNO, PGK, PGK, PNO, PNO, },	// 0
		{ PSB, PSB, PCB, PCB, PSB, PSB, },	// 1
		{ PSB, PSB, PCB, PCB, PSB, PSB, },	// 2
		{ PWB, PWB, PDH, PDH, PWB, PWB, },	// 3
		{ PWB, PCW, PDC, PDC, PCW, PWB, },	// 4
		{ PSH, PCS, POC, POC, PCS, PSH, },	// 5
		{ PSH, PSH, POH, POH, PSH, PSH, },	// 6
		{ PWG, PWS, PCT, PCT, PWS, PWG, },	// 7
		{ PWG, PWG, PCF, PCF, PWG, PWG, },	// 8
	};
	static weUchar	sideTable[SIDE_MAX][DISP_PARAM_POS_CUT_S] = {
		/* 左 ←                           → 右 */
		{   6,   6,  10,  10,  10,  10, },	// SIDE_R
		{  10,  10,  10,  10,   6,   6, },	// SIDE_L
		{  10,  10,  10,  10,  10,  10, },	// SIDE_B
	};
	weInt	aptitude[POS_APT_MAX];
	weInt	apMax;

	weInt	e,s;
	weInt	side;

	#define getAptitude(pr)	playerParamGetAptitudePart( pr, ability)
	// 適性を代入
	aptitude[PCB] = getAptitude( PR_CB);
	aptitude[PSB] = getAptitude( PR_SB);
	aptitude[PDH] = getAptitude( PR_DH);
	aptitude[PWB] = getAptitude( PR_WB);
	aptitude[PCH] = getAptitude( PR_CH);
	aptitude[PSH] = getAptitude( PR_SH);
	aptitude[POH] = getAptitude( PR_OH);
	aptitude[PWG] = getAptitude( PR_WG);
	aptitude[PST] = getAptitude( PR_ST);
	aptitude[PCF] = getAptitude( PR_CF);
	// 特殊適性
	aptitude[PDC] = WE_MAX( getAptitude( PR_DH), getAptitude( PR_CH));
	aptitude[POC] = WE_MAX( getAptitude( PR_OH), getAptitude( PR_CH));
	aptitude[Psb] = getAptitude( PR_SB) * 2 / 4;

	aptitude[PWS] = WE_MAX( getAptitude( PR_WG), getAptitude( PR_ST));
	aptitude[PCW] = WE_MAX( getAptitude( PR_CH), getAptitude( PR_WB));
	aptitude[PCS] = WE_MAX( getAptitude( PR_CH), getAptitude( PR_SH));
	aptitude[PCT] = WE_MAX( getAptitude( PR_CF), getAptitude( PR_ST));


	aptitude[PGK] = (ability->gk ? 10 : 0);
	aptitude[PNO] = 0;

	// 左右の適性
	switch( ability->pos_side ){
	  default:
	  case POS_SIDE__WF:			//利き足側のサイドのみ
		if( ability->lefty )	side = SIDE_L;
		else					side = SIDE_R;
		break;
	  case POS_SIDE__WF_OPPOSITE:	//利き足側と逆のサイドのみ
		if( ability->lefty )	side = SIDE_R;
		else					side = SIDE_L;
		break;
	  case POS_SIDE__BOTH:			//両サイド
	  	side = SIDE_B;
		break;
	}


	// それぞれの適性をセットする
	for( s = 0; s < DISP_PARAM_POS_CUT_S; s++){
		for( e = 0; e < DISP_PARAM_POS_CUT_E; e++){
			weInt	apt;
			apt = aptitude[ positionBlockTable[e][s] ];
			// 左右を補正しなければ
			apt = apt * sideTable[side][s] / 10;
			if( positionBlockTable[e][s] != PNO && positionBlockTable[e][s] != PGK){
				// GK、ポジションなし以外で
				if( all_arounder){
					apt = WE_MAX( apt, 5);	// 5以下にならない
				} else if( flying_man){
					apt = WE_MAX( apt, 10);	// Mr.パーフェクト
				}
			}
			posBlock->aptitude[e][s] = apt;
		}
	}
}


/*============================================================================
	ポジション表の作成
 ============================================================================*/
static weInt playerParamGetAptitudePart( weInt position, PLAYER_ABILITY_PERMANENT *ability)
{
	static const weUchar	pos_fit_list[11][11]	=	{
	// GKとリベロとすWi-パーがない
	//		CB	SB	DH	WB	CH	SH	OH	WG	ST	CF	
		{	10,	6,	6,	5,	5,	5,	5,	5,	5,	5,	},	//CBL,CBLL,CB,CBRR,CBR
		{	7,	10,	5,	8,	5,	5,	5,	5,	5,	5,	},	//LB,RB
		{	6,	5,	10,	5,	8,	5,	5,	5,	5,	5,	},	//DHL,DHLL,DH,DHRR,DHR
		{	5,	8,	6,	10,	6,	8,	5,	5,	5,	5,	},	//LWB,RWB
		{	5,	5,	8,	5,	10,	5,	7,	5,	5,	5,	},	//CHLL CHL CH CHR CHRR
		{	5,	5,	5,	8,	6,	10,	6,	8,	5,	5,	},	//LH,RH
		{	5,	5,	6,	5,	8,	5,	10,	5,	7,	6,	},	//OHL,OHLL,OH,OHRR,OHR
		{	5,	5,	5,	5,	5,	8,	7,	10,	8,	8,	},	//LW,RW
		{	5,	5,	5,	5,	5,	5,	8,	8,	10,	9,	},	//STL,STLL,ST,STRR,STR
		{	5,	5,	5,	5,	5,	5,	5,	7,	8,	10,	}	//CFL,CFLL,CF,CFRR,CFR
	};
	weInt	aptitude;
	aptitude = 0;
	if( ability->cb ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_CB-3]);
	if( ability->sb ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_SB-3]);
	if( ability->dh ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_DH-3]);
	if( ability->wb ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_WB-3]);
	if( ability->ch ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_CH-3]);
	if( ability->sh ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_SH-3]);
	if( ability->oh ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_OH-3]);
	if( ability->wg ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_WG-3]);
	if( ability->st ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_ST-3]);
	if( ability->cf ) aptitude = WE_MAX( aptitude, pos_fit_list[position-3][PR_CF-3]);
	if( aptitude != 10 ){
#if 1
		// 段階を2倍にしてみる
		aptitude = aptitude*2 -10;
		if( aptitude < 0){
			aptitude = 0;
		}
#else
		aptitude -= 2;
		if( aptitude < 0){
			aptitude = 0;
		}
#endif
	}

	return aptitude;
}

/*============================================================================
	選手の数値パラメータを取得
 ============================================================================*/
void playerParamGetParamValue( WE_PID_T pid, PLAYER_PARAM_VALUE *value)
{
	PLAYER_ABILITY_PERMANENT		*ability;
	// 元の能力値を取得
	ability = playerParamGetPlayerParaAbility(pid);
	// 変換
	playerParamAvilityToValue( ability , value );
}


/*============================================================================
	数値パラメータをアビリティに変換
 ============================================================================*/
void playerParamValueToAvility( PLAYER_PARAM_VALUE *value, PLAYER_ABILITY_PERMANENT *ability)
{
	ability->offence      = value->param[PV_OFFENCE     ];
	ability->defence      = value->param[PV_DEFENCE     ];
	ability->atari        = value->param[PV_ATARI       ];
	ability->stamina      = value->param[PV_STAMINA     ];
	ability->dash         = value->param[PV_DASH        ];
	ability->kasoku       = value->param[PV_KASOKU      ];
	ability->response     = value->param[PV_RESPONSE    ];
	ability->agility      = value->param[PV_AGILITY     ];
	ability->dribble      = value->param[PV_DRIBBLE     ];
	ability->dribblespeed = value->param[PV_DRIBBLESPEED];
	ability->passacc      = value->param[PV_PASSACC     ];
	ability->passspeed    = value->param[PV_PASSSPEED   ];
	ability->longacc      = value->param[PV_LONGACC     ];
	ability->longspeed    = value->param[PV_LONGSPEED   ];
	ability->shotacc      = value->param[PV_SHOTACC     ];
	ability->shotpower    = value->param[PV_SHOTPOWER   ];
	ability->shottech     = value->param[PV_SHOTTECH    ];
	ability->freeacc      = value->param[PV_FREEACC     ];
	ability->curve        = value->param[PV_CURVE       ];
	ability->headacc      = value->param[PV_HEADACC     ];
	ability->jump         = value->param[PV_JUMP        ];
	ability->connection   = value->param[PV_CONNECTION  ];
	ability->trap         = value->param[PV_TRAP        ];
	ability->positive     = value->param[PV_POSITIVE    ];
	ability->spirit       = value->param[PV_SPIRIT      ];
	ability->gk_skill     = value->param[PV_GK_SKILL    ];
}


/*============================================================================
	アビリティを数値パラメータに変換
 ============================================================================*/
void playerParamAvilityToValue( PLAYER_ABILITY_PERMANENT *ability, PLAYER_PARAM_VALUE *value)
{
	value->param[PV_OFFENCE     ] = ability->offence     ;
	value->param[PV_DEFENCE     ] = ability->defence     ;
	value->param[PV_ATARI       ] = ability->atari       ;
	value->param[PV_STAMINA     ] = ability->stamina     ;
	value->param[PV_DASH        ] = ability->dash        ;
	value->param[PV_KASOKU      ] = ability->kasoku      ;
	value->param[PV_RESPONSE    ] = ability->response    ;
	value->param[PV_AGILITY     ] = ability->agility     ;
	value->param[PV_DRIBBLE     ] = ability->dribble     ;
	value->param[PV_DRIBBLESPEED] = ability->dribblespeed;
	value->param[PV_PASSACC     ] = ability->passacc     ;
	value->param[PV_PASSSPEED   ] = ability->passspeed   ;
	value->param[PV_LONGACC     ] = ability->longacc     ;
	value->param[PV_LONGSPEED   ] = ability->longspeed   ;
	value->param[PV_SHOTACC     ] = ability->shotacc     ;
	value->param[PV_SHOTPOWER   ] = ability->shotpower   ;
	value->param[PV_SHOTTECH    ] = ability->shottech    ;
	value->param[PV_FREEACC     ] = ability->freeacc     ;
	value->param[PV_CURVE       ] = ability->curve       ;
	value->param[PV_HEADACC     ] = ability->headacc     ;
	value->param[PV_JUMP        ] = ability->jump        ;
	value->param[PV_CONNECTION  ] = ability->connection  ;
	value->param[PV_TRAP        ] = ability->trap        ;
	value->param[PV_POSITIVE    ] = ability->positive    ;
	value->param[PV_SPIRIT      ] = ability->spirit      ;
	value->param[PV_GK_SKILL    ] = ability->gk_skill    ;
}


/*============================================================================
	ランクに応じた文字列を取得
 ============================================================================*/
weChar *playerParamGetRankString( weInt rank)
{
	static weInt rank_list[] = 
	{
		WE_STR_DATA_WCM2_W_000, // "★" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_001, // "★★" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_002, // "★★★" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_003, // "★★★★" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_004, // "★★★★★" 選手の強さを表す、星が多いほど強い
	};
	// ランクの範囲が 1～5 なので一つ減らす
	rank--;
	if( rank >= numberof( rank_list ) ){
		rank = 0;
	}
	return weStringGetString( rank_list[rank]);
}

/*============================================================================
	ランクに応じた文字列を取得(短い)
 ============================================================================*/
weChar *playerParamGetRankShortString( weInt rank)
{
	static weInt rank_list[] = 
	{
		WE_STR_DATA_WCM2_W_005, // "★1" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_006, // "★2" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_007, // "★3" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_008, // "★4" 選手の強さを表す、星が多いほど強い
		WE_STR_DATA_WCM2_W_009, // "★5" 選手の強さを表す、星が多いほど強い
	};
	// ランクの範囲が 1～5 なので一つ減らす
	rank--;
	if( rank >= numberof( rank_list ) ){
		rank = 0;
	}
	return weStringGetString( rank_list[rank]);
}

/*============================================================================
	選手のランクを取得
		重いので、他のパラメータも同時に取得するときは
		playerParamMakeDispParam を使うこと
 ============================================================================*/
weChar playerParamGetRank( WE_PID_T pid)
{
	PLAYER_DISP_PARAM_WORK param;

	if( pid == PID_DUMMY_PLAYER ){
		return 1;
	}
	playerParamMakeDispParam( pid, &param);
	return param.rank;
}

/*============================================================================
	選手のポジションを取得
 ============================================================================*/
weChar playerParamGetPosition( WE_PID_T pid)
{
	PLAYER_ALL_DATA		*all,all_w;
	PLAYER_ABILITY_PERMANENT		*ability;
	if( pid == PID_DUMMY_PLAYER ){
		return PR_GK;
	}
#if WII_MII == 1
	if( PID_MII_TOP <= pid && pid <= PID_MII_END){
		// もともとMii選手が登録されている
		MII_CREATE_ID	create_id;
		all = &all_w;
		// Miiを特定する
		playerMiiSetCreateIDByPID( &create_id, pid);
		// パラメータ作成
		playerMiiSetParamByMiiCreateID( all, &create_id);
		ability = &all->para.ability;
	} else {
		ability = playerParamGetPlayerParaAbility(pid);
	}
#else

	ability = playerParamGetPlayerParaAbility(pid);

#endif
	return ability->position;
}

