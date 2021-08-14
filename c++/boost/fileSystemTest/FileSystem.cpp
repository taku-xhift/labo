

#include <iostream>
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;

int main()
{
	namespace fs = boost::filesystem;
	string path_string = "./fileSystemTest"; // どこをみる？

	//fs::path p(path_string, fs::native);
	fs::path p(path_string);

	if (!fs::is_directory(p)) {
		std::cout << "not directory" << std::endl;
		return 0;
	}

	// 一覧表示.
	fs::directory_iterator end;
	for (fs::directory_iterator it(p); it!=end; ++it) {
		// leaf() パス情報を切って、ファイルの名前部分のみ取り出し
		cout << it->leaf() << endl;
	}

	return 0; 
}

