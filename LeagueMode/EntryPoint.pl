
use Inline CPP;

print main

__END__
__CPP__

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


