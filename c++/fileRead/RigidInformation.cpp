

#include <fstream>
#include <iostream>


#include "RigidInformation.hpp"


using namespace ReseedEngine::Physics;





//! \brief �p�����[�^���t�@�C������ǂݎ��֐�
void RigidInformation::readFromFile(const std::string &path)
{
	std::ifstream ifs(path.c_str());
	std::string buf;

	while(ifs && getline(ifs, buf)) {
		std::cout << buf << std::endl;
	}


}



