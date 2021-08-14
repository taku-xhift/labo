#include <iostream>
#include <vector>
#include <boost/smart_ptr.hpp>

using namespace std;

int main()
{
	vector<int> Vector;
	int vertexNumber = 4;
	int floatNunber = vertexNumber * 4;
	int zero = 0;

	for (int i = 0; i < vertexNumber * 3; ++i) {
		Vector.push_back(i);
	}

	//float Array[floatNunber];
	boost::shared_array<int> vertexHolder(new int[floatNunber]);
	//int* vertexHolder = new int[floatNunber];

	for (int i = 0; i < vertexNumber; ++i) {
		for (int j = 0; j < 3; ++j) {
			vertexHolder[4 * i + j] = Vector[3 * i + j];
		}

		vertexHolder[4 * i + 3] = 0;
	}

	for (int i = 0; i < floatNunber; ++i) {
		cout << vertexHolder[i] << endl;
	}

	/*for (int i = 0; i < floatNunber; ++i) {
		printf("%d\n", vertexHolder[i]);
	}*/

	//delete [] vertexHolder;
	return 0;
}


