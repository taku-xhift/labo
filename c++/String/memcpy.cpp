


#include <iostream>
#include <string>
#include <cstdlib>


class Test
{
public:
	std::string string_;
};


int main()
{
	Test test;
	std::string out;

	{
		// 構造体のケース/////////////////////////////////
		Test localTest;
		localTest.string_ = "テスト";

		test = localTest;
		//memcpy(&test, &localTest, sizeof(Test));
		std::cout << test.string_ << std::endl;


		// string 単体のケース/////////////////////////////////
		std::string in = "sample";
		out = in;
		//memcpy(&out, &in, sizeof(std::string));
		std::cout << out << std::endl;

		std::cout << "scope out" << std::endl;
	}

	std::cout << test.string_ << std::endl;
	std::cout << out << std::endl;
}

