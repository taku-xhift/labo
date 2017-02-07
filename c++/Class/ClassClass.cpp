

#include <iostream>

namespace sample {

class Test
{
	class SubTest
	{
	public:
		SubTest();

		int getInteger();
		int integer;
	};

public:
	int getInteger() { return this->subTest.getInteger(); }

private:
	SubTest subTest;
};

Test::SubTest::SubTest()
	: integer(3)
{
	
}

} // namespace sample

int sample::Test::SubTest::getInteger() {
	return this->integer;
}


int main()
{
	sample::Test test;

	std::cout << test.getInteger() << std::endl;

	return 0;
}
