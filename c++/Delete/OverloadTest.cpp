
/**
 * @file
 * @brief delete のオーバーロードのテスト
 *
 * @author Takuya Shishido
 * @date 2009.11.25 10:50:01
 *
 * @version 0.01, Shishido Takuya, 2009.11.25 10:50:01
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#include <iostream>

#define Delete(ptr) (::operator delete(ptr, __FILE__, __LINE__))

void operator delete(void* data, const char* file_, unsigned int line_)
{
	std::cout << "file : " << file_ << std::endl;
	std::cout << "line : " << line_ << std::endl;

	free(data);
}


class Test
{
public:
	int integer;

	Test()
		: integer(0)
	{ }
};


int main()
{
	Test* test = new Test();


	//unsigned int line = __LINE__;
	//::operator delete (test, __FILE__, line);
	Delete test;


	return 0;
}


