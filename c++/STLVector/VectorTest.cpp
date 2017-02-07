#include <vector>
#include <iostream>





int main()
{
	std::vector<float> floatArray;

	floatArray.resize(10);


	std::cerr << floatArray.size() << std::endl;

	std::cerr << floatArray[floatArray.size()-1] << std::endl;

	return 0;
}






