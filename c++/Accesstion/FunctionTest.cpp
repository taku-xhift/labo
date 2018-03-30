//
// ここでは継承先での関数の呼び出し方について検証する。
//     検証事由    継承先での継承もとの関数の呼び出しについて
//     結論        スコープを明確化することで継承もとの関数と同名の関数を所有していた場合に
//                     しっかりとした呼びわけができることを再確認した。



#include <iostream>


class Super
{
public:
	Super()
	{
		std::cerr << "Constructor of Super." << ::std::endl;
	}

	void init()
	{
		this->check1 = 1.0f;
		this->check2 = 1.0f; 
		this->class
	}


	float   check1;
	float   check2;
};


class Child    : public Super
{
public:
	Child()
	{
		::std::cerr << "Constructor of Child." << ::std::endl;
	}

	void init()
	{
		this->check1 = 2.0f;
		this->check2 = 2.0f;
		this->check3 = 2.0f;
		this->check4 = 2.0f;

		Super::init();
	}


	float check3;
	float check4;

};




int main()
{
	//Super super;
	Child child;


	child.init();


	::std::cerr << child.check1 << ::std::endl;
	::std::cerr << child.check2 << ::std::endl;
	::std::cerr << child.check3 << ::std::endl;
	::std::cerr << child.check4 << ::std::endl;


	return 0;
}




