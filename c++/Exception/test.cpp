#include <iostream>


// 例外ベースクラス
class LibrariesException    : public ::std::exception
{
public:

	// ::std::exception から引き継いだ virtual 関数
	virtual const char* what() const throw()
	{
		return "Libraries Exception";
	}
};

// 例外ベースクラスを継承してきた実装用のベースクラス
class PhysicsException    : public LibrariesException
{
public:

	// LibrariesException の Virtual 関数を引き継いだ関数
	virtual const char* what() const throw()
	{
		return "Physics Exception";
	}


	// 今回改めてここで定義した自分が使用するための例外関数。
	//     これは初期化されていない可能性がある場合に文字列を出力するための関数です。
	//     使われている場面は ExceptionTest::initializedCheck() だけで、
	//     その関数は private になっているので、ユーザーがそれを知ることはありません。
	void initializedCheck() const throw(PhysicsException)
	{
		std::cout << "InitializeError!! (You should check parameter what is initalized.)" << std::endl;
		throw PhysicsException();
	}
};


// 今回はこれの関数を使って例外クラスの例を作っています。
class ExceptionTest
{
private:

	// 下の関数に呼ばれる関数です。
	//     中身は初期化されているかどうかをチェックするための関数です。
	//     例外として PhysicsException を throw します。
	void initialaizedCheck(int i) throw(PhysicsException)
	{
		if (i == NULL) {
			throw PhysicsException();
		}
	}


public:
	// これは上の関数を利用して完成する関数です。
	//     initializedCheck をしてから和を計算し返します。
	int AdditionalReturner (int a, int b) throw(PhysicsException)
	{
		int Int;

		try {
			this->initialaizedCheck(a);
			this->initialaizedCheck(b);
		} catch (PhysicsException& pe) {
			pe.initializedCheck();
			//throw PhysicsException();    // initializedCheck() 内部で throw するべきかは議論の余地があると思います。
		}

		Int = a + b;

		return Int;
	}
};


int main()
{
	// 初期化せずに使うためのパラメータ群
	int sum = 0;
	int parameter = 0;
	ExceptionTest exceptionTest;


	// こっからがチェックするためのテストフィールド。
	try {
		// これはユーザーに公開している関数。
		//     内部で initializedCheck が入っていることはユーザーは知らなくていい。
		sum = exceptionTest.AdditionalReturner(parameter, parameter);

		// 上が例外を出していなければ出力。
		std::cout << sum << std::endl;

	} catch (LibrariesException& le) {

		// キャッチは例外ベースクラスで、共通の Virtual 関数を呼び出すだけでチェックはできる。
		//     今回でいえば PhysicsException がエラーを吐いていることがチェックできる。
		std::cout << le.what() << std::endl;
	}

	return 0;
}

