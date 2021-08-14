
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
	//_CrtSetBreakAlloc( num );    // num �͎擾���ꂽ�ԍ�

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


