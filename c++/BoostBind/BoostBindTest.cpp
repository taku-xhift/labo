

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
		// 7以上12以下の最初の要素を探す。
		// is_orderedに定数をbindして（くくりつけて）、
		// 「is_ordered(7,第一引数,12)」と等価な
		// 関数オブジェクトを作っているわけです。

		int arr[] = {1,2,3,4,5,6,7,8,9,10};
		const int len = sizeof(arr) / sizeof(arr[0]);

		int* f = find_if( arr, arr+len,
		  boost::bind(is_ordered, 7, _1, 12) );
		cout << *f << endl;
	}
	{
		//// 各文字列の１番目から３文字を順にcoutへ出力する。
		//// 「第一引数.substr( 1, 3 )」と等価な関数オブジェクトを
		//// 作っています。bindにメンバ関数を渡すと、
		//// 自動的にクラス変数を第一引数に取る関数に
		//// 読み替えてくれます。
		//// boost::mem_fn参照のこと。

		//string arr[] = {"hello","my_name","is_k","inaba.","bye!"};
		//const int len = sizeof(arr) / sizeof(arr[0]);

		//transform( arr, arr+len, ostream_iterator<char>(cout),
		//  boost::bind(&string::substr, _1, 1, 3) );
		//cout << endl;
	}
	{
		//// 大きい順に並べ替え。
		//// 「less<int>()(第二引数、第一引数)」
		//// と等価な関数オブジェクトです。引数を逆にしただけ。

		//int arr[] = {7,3,4,9,1,2,5,8};
		//const int len = sizeof(arr) / sizeof(arr[0]);

		//sort( arr, arr+len,
		//	boost::bind(less<int>(), _2, _1) );
		//copy( arr, arr+len, ostream_iterator<int>(cout) );
		//cout << endl;
	}

	return 0;
}


