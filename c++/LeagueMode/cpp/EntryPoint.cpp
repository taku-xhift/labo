/**
 * @file
 * @brief エントリーポイント。これを使って perl から呼び出しをしてもらう。
 *
 * @author Takuya Shishido
 * @date   2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "LeagueModeManager.hpp"
#include "StreamObject.hpp"
#include "MemoryLeakCheck.hpp"



using namespace so;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		// ゲーム用の処理が全て終わるまでループする
		while (LeagueMode::LeagueModeManager::getInstance()->getNowState() != LeagueMode::MANAGERSTATE_END) {
			LeagueMode::LeagueModeManager::getInstance()->run();
		}

		out << "\n\n\n\nThe Game is Over." << endl;

		LeagueMode::LeagueModeManager::destroyInstance();

	}

	_CrtDumpMemoryLeaks();

	return 0;
}


