/*
	HeaderFile と関数の関係性についてチェック。
	結論からいうと、よくわからない。
	Header に宣言だけしてソースファイルに中身を書いて
	なぜ認識されないかがわからない。
	あとで聞いて見るといいかもしれない。
*/



#include <iostream>

#include "VoidArray.hpp"



int main()
{
	VoidArray voidArray;
	voidArray.voidData = 2.3f;

	std::cout << voidArray.value<int> () << std::endl;

	return 0;
}


