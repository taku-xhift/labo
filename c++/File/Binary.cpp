

#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::string outfile = "miku.pmd";  //読み込むファイルの指定

	std::ifstream fin(outfile.c_str(), std::ios::in | std::ios::binary);

	//  ファイルを開く
	//  ios::in は読み込み専用  ios::binary はバイナリ形式
	if (!fin) {
		std::cout << "ファイル file.txt が開けません";
		return 1;
	}

	//  ファイルが開けなかったときの対策
	double d;  //文字列ではないデータ

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

	fin.close();  //ファイルを閉じる

	return 0;
}

