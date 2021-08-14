use strict;
use warnings;
#use Inline 'reportbug', 'force', 'info', 'noclean';
#/cygdrive/d/soccer/OnlineTest/TestServer/ForBrower/LeagueModeOperation/src
use Inline CPP => Config => LIBS => '-L/lib/gcc/i686-pc-cygwin/3.4.4 -lLeagueMode -lstdc++ -lgcc',
                            INC => '-I/lib/gcc/i686-pc-cygwin/3.4.4/include';
use Inline CPP => <<'END_OF_CPP';


#include <iostream>
#include "LeagueMode/CInterfaceLeague/CInterface_LeagueMode.hpp"

void teamSelect() {
    LeagueMode_TeamSelect();
    std::cout << "LeagueMode_TeamSelect()" << std::endl;
}

void sampleTest() {
    LeagueMode_ForwardGame("アーセナル", "アストン ヴィラ");
    std::cout << "LeagueMode_AutoGame()" << std::endl;
}

void testtest() {
    LeagueMode_TestGame();
    std::cout << "LeagueMode_TestGame()" << std::endl;
}


END_OF_CPP


teamSelect();
sampleTest();
#autoGames();
#testtest();


