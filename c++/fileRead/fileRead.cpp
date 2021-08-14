



// ファイルから読み出したものを画面に全て出力


#include "RigidInformation.hpp"


using namespace ReseedEngine::Physics;



int main()
{
	RigidInformation information;

	information.readFromFile("data.txt");

	return 0;
}





