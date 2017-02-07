


#include <iostream>
#include <Windows.h>
#include "D:/PersonalTool/xyzzy/laboratory/c++/Dll/Export/TestClass.hpp"


//class __declspec(dllimport) mode::TestClass;

int main() {
	HINSTANCE hDll = LoadLibraryEx("DllExport.dll", NULL, 0);
	if (!hDll) {
		std::cerr << "open err" << std::endl;
		return 1;
	}


	mode::TestClass test;
	std::cout << test.getInteger() << std::endl;

	test.setInteger(573);
	std::cout << test.getInteger() << std::endl;

	test.print<int>();
}

