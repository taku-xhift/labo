
// 子供クラスの保存方法についての実験

// 結論
// クラスのメンバとして保存することは可能だが、
// Super class をメンバとして保存する場合にはいいが、
// 子供のクラス型でメンバを持っていた場合には
// Super class の保存方法がないので注意が必要。

// 用はデータの形が変わる可能性がある場合には
// 親のクラス型でデータを持っておくといい。

//---------------------------------------------
//  問題点
//---------------------------------------------
// 親クラス型でデータを保持していると、例えばデータを取り出したい場合に
// 子クラスを渡して格納したとしても取り出し方が親クラス分子か取り出せない



#include <iostream>

class Super
{

};

class Child : public Super
{

};


class Save
{
public:
	Child child;
	Super super;

	//void cout(Child &child)
	//{
	//	::std::cerr << "Success!" << ::std::endl;
	//}

	void cout(Super &super)
	{
		::std::cerr << "Success!" << ::std::endl;
	}
};




int main()
{
	Save save;
	Child child;
	Super super;

	//save.child = super;
	save.super = child;
//	save.child = super;

	//save.cout(super);
	save.cout(child);

	return 0;
}


