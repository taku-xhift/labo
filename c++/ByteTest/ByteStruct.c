

#include <stdio.h>
#include <stdlib.h>

typedef struct {
unsigned int	lefty				:1;	/*!<利き足					01bits*/ \
unsigned int	freetype			:4;	/*!<フリーキックタイプ		05bits*/ \
unsigned int	pk_type				:3;	/*!<ペナルティキックタイプ	08bits*/ \
unsigned int	dribble_type		:2;	/*!<ドリブルタイプ			10bits*/ \
unsigned int	feedkick_type		:2;	/*!<フィードキックタイプ	12bits*/ \
unsigned int	position			:4;	/*!<1stポジション			16bits*/ \
unsigned int	offence				:7;	/*!<オフェンス				23bits*/ \
unsigned int	gk					:1;	/*!<GK適正					24bits*/ \
unsigned int	defence				:7;	/*!<ディフェンス			31bits*/ \
unsigned int	sw					:1;	/*!<SW適正					32bits	04bytes*/ \
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


