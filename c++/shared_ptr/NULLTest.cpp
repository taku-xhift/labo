
// 得られた結論

// boost::shared_ptr は宣言した時点ではNULLポインタの様子。
// なので、宣言しただけで実態があるかのように勘違いしないこと。
// あくまでこれはポインタなのだ。




#include <iostream>
#include <boost/shared_ptr.hpp>

class Test
{
public:
	boost::shared_ptr<int> number;
};

int main()
{
	//::boost::shared_ptr<Test> test(new Test());
	Test test;


	if (test.number != NULL) {
		::std::cerr << "Test is Here!" << ::std::endl;
	}


	return 0;
}


