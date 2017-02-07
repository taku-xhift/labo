


#include <iostream>
#include <algorithm>

template<typename T, std::size_t N>
T* begin(T (&ar)[N])
{
	return ar;
}

template<typename T, std::size_t N>
const T* begin(T (&ar)[N])
{
	return ar;
}


template<typename T, std::size_t N>
T* end(T (&ar)[N])
{
	return ar + N;
}

template<typename T, std::size_t N>
const T* end(T (&ar)[N])
{
	return ar + N;
}

template<typename Range>
void sort(Range& r)
{
	std::sort(begin(r), end(r));
}


void main()
{
	//float *floatArray = new float[100];
	float floatArray[100];
	floatArray[99] = 100.0f;

	std::cout << *end(floatArray) << std::endl;

	//delete [] floatArray;
}

