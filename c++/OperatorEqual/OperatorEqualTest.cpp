

#include <iostream>

class Test
{
public:

	float floating;
	void* data;
	unsigned int dataSize;

	Test()
	{
	}
};


class BindData
{
public:

	float floating;
	void* data;

	BindData(void* data_, float floating_ = 3.0f)
		: floating(floating_)
		, data(data_)
	{
	}


	operator Test()
	{
		Test test;

		test.data = this->data;
		test.dataSize = sizeof((this->data));
		test.floating = this->floating;

		return test;
	}
};




int main()
{
	float *floating = new float;
	*floating = 20.0f;
	float floating2 = 50.0f;

	BindData bindData(floating, floating2);

	Test test = bindData;


	std::cout << test.floating << std::endl;
	std::cout << *(float *)(test.data) << std::endl;
	std::cout << test.dataSize << std::endl;


	delete floating;
	return 0;
}

