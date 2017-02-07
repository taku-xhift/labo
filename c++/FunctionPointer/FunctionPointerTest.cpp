
/*
 * @note
 *      メンバ関数ポインタはデータを保存するのに
 *      どのクラスの関数ポインタなのかを保存しなくてはいけないので
 *      全てのクラスの関数を保存するようなグローバルメンバを作ることはできない。
 *
 *      関数ポインタを使って、あるボタンを押したら
 *      データがプリントされるようなメソッドを作りたかった。
 *      しかしそれは非常に面倒くさそうだったので、却下。
 *      以下は、失敗したもの。
 * 
 *      コールバックのコンテナって考え方の方がいいのかも。。
*/

#include <iostream>
#include <vector>

//std::vector<void*> fpContainer;


void out() {
	std::cout << "Out of Global." << std::endl;
}

void (*userFunc)(void) = out;


class Test
{
public:

	void out() {
		std::cout << "Out of Test." << std::endl;
	}

	Test()
	{
		userFunc = (&Test::out);
	}
};


int main()
{
	out();

	return 0;
}


