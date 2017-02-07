

#include <iostream>
#include "weoJsonParser.h"


int main() {
	std::string file;

	// ファイルリード
	{
		std::ifstream ifs;
		std::string temp;
		ifs.open("C:\\Documents and Settings\\usr10029479\\My Documents\\KONAMI\\Winning Eleven Online\\MyTeamData.dat", std::ios::in);
		if (ifs) {
			while (ifs.eof() == false) {
				ifs >> temp;
				file += temp;
			}
		}
		ifs.close();
	}

}

