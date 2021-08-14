

#include <stdio.h>
#include <stdlib.h>

typedef struct {
unsigned int	lefty				:1;	/*!<������					01bits*/ \
unsigned int	freetype			:4;	/*!<�t���[�L�b�N�^�C�v		05bits*/ \
unsigned int	pk_type				:3;	/*!<�y�i���e�B�L�b�N�^�C�v	08bits*/ \
unsigned int	dribble_type		:2;	/*!<�h���u���^�C�v			10bits*/ \
unsigned int	feedkick_type		:2;	/*!<�t�B�[�h�L�b�N�^�C�v	12bits*/ \
unsigned int	position			:4;	/*!<1st�|�W�V����			16bits*/ \
unsigned int	offence				:7;	/*!<�I�t�F���X				23bits*/ \
unsigned int	gk					:1;	/*!<GK�K��					24bits*/ \
unsigned int	defence				:7;	/*!<�f�B�t�F���X			31bits*/ \
unsigned int	sw					:1;	/*!<SW�K��					32bits	04bytes*/ \
} Parameter;



int main()
{
	Parameter* parameter = malloc(sizeof(Parameter));


	parameter->freetype = 4.0f;
	parameter->lefty = 6.0f;
	parameter->offence = 43;

	printf("freetype = %d\n", parameter->freetype);
	printf("lefty = %d\n", parameter->lefty);
	printf("offence = %d\n", parameter->offence);

	free(parameter);

	return 0;
}


