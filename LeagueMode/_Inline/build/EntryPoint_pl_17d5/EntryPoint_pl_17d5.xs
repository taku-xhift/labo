#ifndef bool
#include <iostream>
#endif
extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"
}
#ifdef bool
#undef bool
#include <iostream>
#endif


/**
 * @file
 * @brief �G���g���[�|�C���g�B������g���� perl ����Ăяo�������Ă��炤�B
*/


#include <stdio.h>
#include <string.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeCushion.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/CInterfaceLeague/CInterface_LeagueMode.hpp"

#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"


int main()
{
//leakCheckStart();
//setBreakAlloc( 422 );    // num �͎擾���ꂽ�ԍ�

{
/*	while (1) {
		const char* state = leagueModeCushion();
		printf("%s\n", state);

		if (strcmp(state, gameEnd) == 0) {
			break;
		}
	}
*/

	LeagueMode_TeamSelect();
	LeagueMode_AutoGame(manchesterUnited, chercy);

	printf("\n\n\n");
	printf("The Game is End.\n");
}

//leakCheckEnd();

	return 0;
}


MODULE = EntryPoint_pl_17d5     	PACKAGE = main	

PROTOTYPES: DISABLE

int
main()
    
