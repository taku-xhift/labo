


#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

typedef float                                RealNumber;
typedef boost::numeric::ublas::matrix<float> Matrix44;


Matrix44 mtxMulTranslate(Matrix44 matrix, RealNumber x, RealNumber y, RealNumber z) throw()
{
	matrix(0, 3) += matrix(0, 0)*x + matrix(0, 1)*y + matrix(0, 2)*z;
	matrix(1, 3) += matrix(1, 0)*x + matrix(1, 1)*y + matrix(1, 2)*z;
	matrix(2, 3) += matrix(2, 0)*x + matrix(2, 1)*y + matrix(2, 2)*z;
	matrix(3, 3) += matrix(3, 0)*x + matrix(3, 1)*y + matrix(3, 2)*z;
	return matrix;
}


int main()
{
	Matrix44 matrix = boost::numeric::ublas::identity_matrix<float> (4);

	mtxMulTranslate(matrix, 2.0f, 2.0f, 2.0f);




	return 0;
}

