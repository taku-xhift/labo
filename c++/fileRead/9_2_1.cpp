#include <iostream>
#include <fstream>


int main()
{
	std::ofstream fout("test");

	if (!fout) {
		std::cout << "Couldn't open the file." << std::endl;
		return 1;
	}

	fout << "Hello!\n";
	fout << 100 << ' ' << std::hex << 100 << std::endl;

	fout.close();

	std::ifstream fin("test");

	if (!fin) {
		std::cout << "Couldn't open the file." << std::endl;
		return 1;
	}


	char str[80];
	int i;

	fin >> str >> i;
	std::cout << str << ' ' << i << std::endl;

	fin.close();


	return 0;
}




