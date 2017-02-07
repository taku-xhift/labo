


#include <iostream>


int CreatableCheck(int i, int j, int k) {
	const int iSquere = i*i;
	const int jSquere = j*j;
	const int kSquere = k*k;

	return (iSquere == jSquere + kSquere)
		? i + j + k
		: (jSquere == iSquere + kSquere)
			? i + j + k
			: (kSquere == iSquere + jSquere)
				? i + j + k
				: 0;
}


int main()
{
	const int size = 4;
	int array[size] = {4,5,10,20};

	int returnVal = 0;

	for (int i = 0; i < size-2; ++i) {
		for (int j = i+1; j < size; ++j) {
			for (int k = j+1; k < size; ++k) {
				returnVal = CreatableCheck(array[i], array[j], array[k]);
				if (returnVal) {
					std::cout << "i => " << array[i] << "\n"
					             "j => " << array[j] << "\n"
					             "k => " << array[k] << "\n"
					             "Sum => " << array[i] + array[j] + array[k] << "\n";
					break;
				} else {
//					std::cout << "i => " << array[i] << "\n"
//					             "j => " << array[j] << "\n"
//					             "k => " << array[k] << "\n=====================================\n";
				}
			}
		}
	}

	if (!returnVal) {
		std::cout << "0";
	}

}


