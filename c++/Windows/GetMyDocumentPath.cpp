


#include <Shlobj.h>
#include <iostream>
#include <string>


std::string getMyDocumentPath() {
	const unsigned int bufferSize = 0xff;

	LPITEMIDLIST pidlist;
	WCHAR SpecialPath[bufferSize];
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidlist );
	SHGetPathFromIDList( pidlist, SpecialPath );

	char myDocumentPath[bufferSize * 2];
	size_t wLen = 0;
	errno_t err = 0;
	err = wcstombs_s(&wLen, myDocumentPath, sizeof(myDocumentPath)/sizeof(char), SpecialPath, _TRUNCATE);

	return std::string(myDocumentPath);
}


int main() {
	std::string myDocumentPath = getMyDocumentPath();
	std::cout << myDocumentPath.c_str() << std::endl;
}

