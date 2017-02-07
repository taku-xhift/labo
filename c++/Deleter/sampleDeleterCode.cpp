

class X
{
public:

	~X()
	{
		std::cout << "X::~X" << std::endl;
	}
};

class B
{
public:

	~B() // virtual でないことに注意！！
	{
		std::cout << "B::~B" << std::endl;
	}
};

class D : public B
{
public:

	~D()
	{
		std::cout << "D::~D" << std::endl;
	}
};

int main()
{
	{
		boost::shared_ptr< void > px( new X() ); // void * のように見えるけれど……
	} // ここでちゃんと X::~X が走る！

	{
		boost::shared_ptr< B > pb( new D() ); // デストラクタが仮想でない基底クラスのスマポに
		// 派生クラスのポインタを代入．大丈夫か？
	} // ちゃんと D::~D も呼ばれます！
}
