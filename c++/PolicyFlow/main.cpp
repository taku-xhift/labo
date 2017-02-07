/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.10.07 15:20:08
 *
 * @version 0.01, Shishido Takuya, 2010.10.07 15:20:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#include <windows.h>

#include "Modeler.hpp"
#include "Viewer.hpp"
#include "Controler.hpp"
#include "Define.hpp"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( num );    // num ÇÕéÊìæÇ≥ÇÍÇΩî‘çÜ

	{
		ControlManager controlManager;
		controlManager.add(new Controler<LeagueFlow>());

		int count = 1;
		while(true) {
			controlManager.execute(count);
			if (controlManager.getControlInterfaceSize() == 0) {
				break;
			}
			std::cin >> count;
		};
	}

	 _CrtDumpMemoryLeaks();

	return 0;
}


