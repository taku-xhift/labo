#include <vector>
#include <algorithm>
#include <iostream>


template <typename T>
class OutPut
{
public:

	OutPut()
	{
		std::cout << "Called OutPutConstructor." << std::endl;
	}

	~OutPut()
	{
		std::cout << "Called OutPutDestructor." << std::endl;
	}

	void operator()(const T& num)
	{
		std::cout << num << std::endl;
	}
};


int main()
{
	std::vector<float> nums;

	for (int i = 0; i < 5; ++i) {
		nums.push_back( static_cast<float>(i + .5f) );
	}


	std::for_each( nums.begin(), nums.end(), OutPut<float>() );


	return 0;
}


