
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
	TEAMLIST_MAX,
} TeamList;


static const char* dataBaseFileName = "game_para.csv";      //!< �`�[���f�[�^�������Ă���t�@�C��
static const char* dataBaseResultFileName = "result.txt";   //!< ���낢��Ȍ��ʂ������o���t�@�C��
static const char* resultFileName = "result";               //!< �������ʂ������o���t�@�C��
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
//static const int   teamNumber = 31;                       //!< �P�`�[���̐l��
#define teamNumber 35
/*
#define dataBaseFileName  "game_para.csv"
#define resultFileName "result"
#define manchesterUnited "�}���`�F�X�^�[ ���i�C�e�b�h"
#define chercy "�`�F���V�["
*/
#endif

