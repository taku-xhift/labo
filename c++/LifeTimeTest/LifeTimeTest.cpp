#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

typedef boost::numeric::ublas::matrix<float> Matrix44;


const Matrix44 &getWorldMatrix()
{
	Matrix44 matrix = boost::numeric::ublas::identity_matrix<float> (4);
	return matrix;
}



int main()
{
	const Matrix44 &matrix = getWorldMatrix();


	std::cout << matrix(0, 0) << std::endl;

	return 0;
}

