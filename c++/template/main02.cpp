#include <iostream>
using namespace std;

int main()
{
	cout << "�J�n" << endl;

	try {
		cout << "try�u���b�N�̓���" << endl;
		throw 10;
		cout << "���s����Ȃ��u���b�N" << endl;
	}

	catch (int i) {
		cout << "�ߊl�I�����́F" << i << endl;
	}

	cout << "�I��" << endl;

	return 0;
}
