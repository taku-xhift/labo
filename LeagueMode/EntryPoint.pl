
use Inline CPP;

print main

__END__
__CPP__

/**
 * @file
 * @brief エントリーポイント。これを使って perl から呼び出しをしてもらう。
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
//setBreakAlloc( 422 );    // num は取得された番号

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


