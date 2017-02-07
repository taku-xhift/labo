

#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<float> Matrix44;

int main()
{
	Matrix44 matrix(4, 4);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix(i, j) = i * 4 + j;
		}
	}

	std::cout << matrix << std::endl;

	return 0;
}


