


#include <iostream>

using namespace std;


// コンパイル時アサート。 cond が false だとコンパイルエラーが発生する
// 後でもうちょっと書き換え予定
#define STATIC_ASSERT(cond)        extern int assert_function(int [(cond)?1:-1])

//#define CHECKER(cond)   (cond)? void print() { cerr<<"print"<<endl;} : void cout{cerr<<"cout"<<endl;}
#define CHECKER(cond)   void print() { cerr<<((cond)?1:-1)<<endl;}



class Test {
public:

	CHECKER(true);
};


int main() {
	Test test;
	//test.print();
	//STATIC_ASSERT((false));
	//cout << TEST(false) << endl;
#if ()
	TEST(false);
#else
#endif
	//TEST(true);
}


