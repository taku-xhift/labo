#include <iostream>
using namespace std;

int main()
{
	cout << "開始" << endl;

	try {
		cout << "tryブロックの内部" << endl;
		throw 10;
		cout << "実行されないブロック" << endl;
	}

	catch (int i) {
		cout << "捕獲！数字は：" << i << endl;
	}

	cout << "終了" << endl;

	return 0;
}
