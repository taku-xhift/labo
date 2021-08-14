#include <tchar.h>
#include <string>
#include <iostream>


int main()
{
	std::string string;
	{
		char charTest[0xff];
		//char* str = charTest;


		_tcsncpy(charTest, "string Test", 12);
		//_tcsncpy(str, "string Test", 12);

		string = charTest;
	}
	std::cout << string << std::endl;
	//std::cout << str << std::endl;

	return 0;
}


