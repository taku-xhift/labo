

#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::string outfile = "miku.pmd";  //�ǂݍ��ރt�@�C���̎w��

	std::ifstream fin(outfile.c_str(), std::ios::in | std::ios::binary);

	//  �t�@�C�����J��
	//  ios::in �͓ǂݍ��ݐ�p  ios::binary �̓o�C�i���`��
	if (!fin) {
		std::cout << "�t�@�C�� file.txt ���J���܂���";
		return 1;
	}

	//  �t�@�C�����J���Ȃ������Ƃ��̑΍�
	double d;  //������ł͂Ȃ��f�[�^

	char format[0xff];
	float version = .0f;
	char name[0xff];
	char comment[0xff];

	fin.read(format, 3*sizeof(char));
	fin.read((char*) &version, sizeof(float));
	fin.read(name, 20*sizeof(char));
	fin.read(comment, 0xff*sizeof(char));


	std::cout << "format: " << format << std::endl;
	std::cout << "version: " << version << std::endl;
	std::cout << "name: " << name << std::endl;
	std::cout << "comment: " << comment << std::endl;

	fin.close();  //�t�@�C�������

	return 0;
}

