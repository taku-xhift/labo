

#include <iostream>
#include <windows.h>


int main() {
	std::cout <<
		GetPrivateProfileInt(
			L"stadium",
			L"CLUB_HOUSE",
			UINT_MAX,
			L"E:/soccer/WinningElevenOnline/win/tol/BootTool/UseStadium.ini")
		<< std::endl;
}


