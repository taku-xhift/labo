
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<float> Matrix44;
//typedef boost::numeric::ublas

int main()
{
	Matrix44 matrix = boost::numeric::ublas::identity_matrix<float> (4);

	std::cout << matrix << std::endl;

	return 0;
}


