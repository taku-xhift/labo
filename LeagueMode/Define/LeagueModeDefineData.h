
#ifndef LEAGUEMODEDEFINEDATA_H_INCLUDED
#define LEAGUEMODEDEFINEDATA_H_INCLUDED


typedef enum {
	TEAMLIST_ARSENAL,
	TEAMLIST_ASTONVILLA,
	TEAMLIST_BIRMINGHAMCITY,
	TEAMLIST_BLACKBURNROVERS,
	TEAMLIST_BOLTONWANDERERS,
	TEAMLIST_BURNLEYFC,
	TEAMLIST_CHERCY,
	TEAMLIST_EVERTON,
	TEAMLIST_FULHAM,
	TEAMLIST_HULLCITY,
	TEAMLIST_LIVERPOOLFC,
	TEAMLIST_MANCHESTERCITY,
	TEAMLIST_MANCHESTERUNITED,
	TEAMLIST_PORTSMOUTH,
	TEAMLIST_STOKECITY,
	TEAMLIST_SUNDERLAND,
	TEAMLIST_TOTTENHAMHOTSPUR,
	TEAMLIST_WESTHAMUNITED,
	TEAMLIST_WIGANATHLETIC,
	TEAMLIST_WOLVERHAMPTONWANDERERS,
	TEAMLIST_INVALID,           //!< MAX �ȊO�ɉ����Ɏg���ꍇ��
	TEAMLIST_MAX,
} TeamList;


static const char* gameEnd = "GameEnd";                     //!< �Q�[���E�o�p
static const char* nothing = "nothing";                     //!< �����ȕ�����ł��邱�Ƃ���������
static const char* dataBaseFileName = "game_para.csv";      //!< �`�[���f�[�^�������Ă���t�@�C��
static const char* dataBaseResultFileName = "result.txt";   //!< ���낢��Ȍ��ʂ������o���t�@�C��
static const char* resultFileName = "result";               //!< �������ʂ������o���t�@�C��

// �v���~�A���[�O�̓o�^�`�[��
static const char* arsenal = "�A�[�Z�i��";
static const char* astonVilla = "�A�X�g�� ���B��";
static const char* birminghamCity = "�o�[�~���K�� �V�e�B";
static const char* blackburnRovers = "�u���b�N�o�[�� ���[���@�[�Y";
static const char* boltonWanderers = "�{���g�� �����_���[�Y";
static const char* burnleyFC = "�o�[�����[";
static const char* chercy = "�`�F���V�[";
static const char* everton = "�G���@�[�g��";
static const char* fulham = "�t����";
static const char* hullCity = "�n�� �V�e�B";
static const char* liverpoolFC = "�����@�v�[��FC";
static const char* manchesterCity = "�}���`�F�X�^�[ �V�e�B";
static const char* manchesterUnited = "�}���`�F�X�^�[ ���i�C�e�b�h";
static const char* portsmouth = "�|�[�c�}�X";
static const char* stokeCity = "�X�g�[�N �V�e�B";
static const char* sunderland = "�T���_�[�����h";
static const char* tottenhamHotspur  = "�g�b�e�i�� �z�b�g�X�p�[";
static const char* westHamUnited = "�E�F�X�g�n�� ���i�C�e�b�h";
static const char* wiganAthletic = "�E�B�K�� �A�X���`�b�N";
static const char* wolverhamptonWanderers = "�E�H�����@�[�n���v�g�� W.";
//static const int   teamNumber = 31;                       //!< �P�`�[���̐l��


// �L�[�Ɋւ��� Define
static const char* key_DBError = "Error";
static const char* key_PlayerData = "playerdata";
static const char* key_PlayerData_player_id = "playerid";
static const char* key_PlayerData_player_name = "playername";
static const char* key_PlayerData_offence = "offence";
static const char* key_PlayerData_defence = "defence";
static const char* key_TeamData = "TeamData";
static const char* key_TeamData_name = "teamname";
static const char* key_TeamData_ID = "teamid";
static const char* key_TeamData_playerNumber = "teamPlayerNumber";
static const char* key_TeamData_players = "teamplayers";


// �G���[������ɑ΂��� Define
static const char* DBErr_NoError = "errnoerror";
static const char* DBErr_NotFound = "errnotfound";
static const char* DBErr_CommandError = "errcomand";
static const char* DBErr_InvalidData = "errinvaliddata";
static const char* DBErr_DBError = "errdberror";
static const char* DBErr_CriticalError = "criticalerror";




static const int home = 0;
static const int away = 1;
static const int homeAwayMax = 2;

#define team_playerNumber 35

#endif

