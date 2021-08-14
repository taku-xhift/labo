


#include <iostream>


int main()
{
	unsigned int size;
	{
		class Sample
		{
		public:
			float container[16];
		};

		size = sizeof(Sample);

		//float container[16];
		//size = sizeof(contaner);
	}

	std::cout << size << std::endl;


	std::cout << 4 * 16 << std::endl;

	return 0;
}




