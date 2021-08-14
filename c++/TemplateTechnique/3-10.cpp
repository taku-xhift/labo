


#include <iostream>
#include <iterator>


template<typename Iterator>
void selectionSort(Iterator first, Iterator last)
{
	for (Iterator p = first; p != last; ++p) {
		Iterator minPosition = p;
		for (Iterator q = p; q != last; ++q) {
			if (*minPosition > *q) {
				minPosition = q;
			}
		}

		typename std::iterator_traits<Iterator>::value_type tmp =
			*minPosition;
		*minPosition = *p;
		*p = tmp;
	}
}


int main()
{
	int array[4];
	for (int i = 0; i < 4; ++i) {
		array[i] = 4-i;
	}

	selectionSort(array, &array[4]);

	for (int i = 0; i < 4; ++i) {
		std::cout << array[i] << std::endl;
	}

	return 0;
}



