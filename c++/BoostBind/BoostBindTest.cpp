

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>
using namespace std;

bool is_ordered( int a, int b, int c )
{
	return a<=b && b<=c;
}

int main()
{
	{
		// 7�ȏ�12�ȉ��̍ŏ��̗v�f��T���B
		// is_ordered�ɒ萔��bind���āi��������āj�A
		// �uis_ordered(7,������,12)�v�Ɠ�����
		// �֐��I�u�W�F�N�g������Ă���킯�ł��B

		int arr[] = {1,2,3,4,5,6,7,8,9,10};
		const int len = sizeof(arr) / sizeof(arr[0]);

		int* f = find_if( arr, arr+len,
		  boost::bind(is_ordered, 7, _1, 12) );
		cout << *f << endl;
	}
	{
		//// �e������̂P�Ԗڂ���R����������cout�֏o�͂���B
		//// �u������.substr( 1, 3 )�v�Ɠ����Ȋ֐��I�u�W�F�N�g��
		//// ����Ă��܂��Bbind�Ƀ����o�֐���n���ƁA
		//// �����I�ɃN���X�ϐ���������Ɏ��֐���
		//// �ǂݑւ��Ă���܂��B
		//// boost::mem_fn�Q�Ƃ̂��ƁB

		//string arr[] = {"hello","my_name","is_k","inaba.","bye!"};
		//const int len = sizeof(arr) / sizeof(arr[0]);

		//transform( arr, arr+len, ostream_iterator<char>(cout),
		//  boost::bind(&string::substr, _1, 1, 3) );
		//cout << endl;
	}
	{
		//// �傫�����ɕ��בւ��B
		//// �uless<int>()(�������A������)�v
		//// �Ɠ����Ȋ֐��I�u�W�F�N�g�ł��B�������t�ɂ��������B

		//int arr[] = {7,3,4,9,1,2,5,8};
		//const int len = sizeof(arr) / sizeof(arr[0]);

		//sort( arr, arr+len,
		//	boost::bind(less<int>(), _2, _1) );
		//copy( arr, arr+len, ostream_iterator<int>(cout) );
		//cout << endl;
	}

	return 0;
}


