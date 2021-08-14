#include <iostream>
#include <fstream>



int main(int argc, char *argv[])
{

	//std::ifstream fin("test");

	//fin.write

	WRITE <"test">;


	if (argc != 2) {
		std::cout << "使い方： Write < ファイル名 >\n";
		return 1;
	}

	std::ofstream out(argv[1]);

	if (!out) {
		std::cout << "Couldn't open output File.\n";
		return 1;
	}

	char str[80];
	std::cout << "文字列をディスクに書き込み、＄で停止します\n";

	do {
		std::cout << ": ";
		std::cin >> str;
		out << str << std::endl;
	} while (*str != '$');

	out.close();

	return 0;

}

