

#include <iostream>
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;

int main()
{
	namespace fs = boost::filesystem;
	string path_string = "./fileSystemTest"; // �ǂ����݂�H

	//fs::path p(path_string, fs::native);
	fs::path p(path_string);

	if (!fs::is_directory(p)) {
		std::cout << "not directory" << std::endl;
		return 0;
	}

	// �ꗗ�\��.
	fs::directory_iterator end;
	for (fs::directory_iterator it(p); it!=end; ++it) {
		// leaf() �p�X����؂��āA�t�@�C���̖��O�����̂ݎ��o��
		cout << it->leaf() << endl;
	}

	return 0; 
}

