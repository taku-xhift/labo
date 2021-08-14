

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


typedef boost::numeric::ublas::matrix<float> Matrix44;


int main()
{
	Matrix44 matrix(4, 4);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix(i, j) = 4 * i + j;
		}
	}

	boost::numeric::ublas::prod(matrix, matrix);
	//matrix = boost::numeric::ublas::prod(matrix, matrix);

	std::cout << matrix << std::endl;

	return 0;
}

