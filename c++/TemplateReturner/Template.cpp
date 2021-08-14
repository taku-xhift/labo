


#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Test
{
public:

	T *t;

	Test(T *t_ = NULL)
		: t(t_)
	{
	}

	//operator T() const
	//{
	//	return *t;
	//}

	operator T*() const
	{
		return t;
	}

};


template<typename T>
class Sample
{
	std::string name;
	Test<T> test;
};


int main()
{
	float *floating = new float;
	*floating = 3.0f;
	void *voider;

	voider = floating;
	Test<float> test(floating);

	float *floating2 = test;
	//float *floating2 = (float *)voider;

	//std::cout << *test.t << std::endl;
	//std::cout << floating2 << std::endl;


	delete floating;

	return 0;
}


