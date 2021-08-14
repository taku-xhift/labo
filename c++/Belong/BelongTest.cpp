

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

class Test;
typedef boost::shared_ptr<Test> SpTest;


std::vector<SpTest> spTest;

class Test
{
public:
	float floating;

	Test()
	{
		this->floating = 3.0f;
	}

	~Test()
	{
		std::cout << "Destructored in Test." << std::endl;
	}

	void addTest()
	{
		// 自分自身のスマートポインタを登録したい
		// しかし Double Delete 問題発生中
		//SpTest test(new Test);
		//test.get() = this;
		SpTest test;
		test.px = this;
		spTest.push_back(test);
	}
};



int main()
{
	SpTest test(new Test());

	test->addTest();

	spTest[0]->floating = 4.f;

	std::cout << "test's float is " << test->floating << std::endl;
	std::cout << "spTestVector's float is " << spTest[0]->floating << std::endl;

	return 0;
}


