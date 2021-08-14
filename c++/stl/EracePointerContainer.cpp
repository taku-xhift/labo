


#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)     // ‚±‚ê‚ªd—v
#endif

#include <list>
#include <iostream>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc( num );    // num ‚Íæ“¾‚³‚ê‚½”Ô†

	{
		std::list<int*> container;
		for (int i = 0; i < 10; ++i) {
			container.push_back(new int(i));
		}

		for (std::list<int*>::iterator ite = container.begin(); ite != container.end(); ++ite) {
			std::cout << *ite << std::endl;
		}

		for (std::list<int*>::iterator ite = container.begin(); ite != container.end(); ++ite) {
			delete *ite;
		}
		container.clear();

		//std::list<int*>::iterator ite = container.begin();
		//while (ite != container.end()) {
		//	delete *ite;
		//	container.erase(ite);
		//	ite = container.begin();
		//}
	}


	 _CrtDumpMemoryLeaks();

	return 0;
}


