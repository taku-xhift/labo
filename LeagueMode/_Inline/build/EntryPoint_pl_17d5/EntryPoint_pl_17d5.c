/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of EntryPoint_pl_17d5.xs. Do not edit this file, edit EntryPoint_pl_17d5.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "EntryPoint_pl_17d5.xs"
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


#line 76 "EntryPoint_pl_17d5.c"
XS(XS_main_main); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_main)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::main()");
    {
	int	RETVAL;
	dXSTARG;

	RETVAL = main();
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_EntryPoint_pl_17d5); /* prototype to pass -Wmissing-prototypes */
XS(boot_EntryPoint_pl_17d5)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("main::main", XS_main_main, file);
    XSRETURN_YES;
}

