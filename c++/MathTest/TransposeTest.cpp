#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<float> Matrix44;
typedef boost::numeric::ublas::identity_matrix<float> IdentityMtx44;


Matrix44 transposeMtx(const Matrix44 &matrix)
{
	Matrix44 matrix_ = IdentityMtx44(4);

	matrix_(0, 0) = matrix(0, 0);
	matrix_(0, 1) = matrix(1, 0);
	matrix_(0, 2) = matrix(2, 0);
	matrix_(0, 3) = matrix(3, 0);

	matrix_(1, 0) = matrix(0, 1);
	matrix_(1, 1) = matrix(1, 1);
	matrix_(1, 2) = matrix(2, 1);
	matrix_(1, 3) = matrix(3, 1);

	matrix_(2, 0) = matrix(0, 2);
	matrix_(2, 1) = matrix(1, 2);
	matrix_(2, 2) = matrix(2, 2);
	matrix_(2, 3) = matrix(3, 2);

	matrix_(3, 0) = matrix(0, 3);
	matrix_(3, 1) = matrix(1, 3);
	matrix_(3, 2) = matrix(2, 3);
	matrix_(3, 3) = matrix(3, 3);

	return matrix_;
}


int main()
{
	Matrix44 matrix(4, 4);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix(i, j) = 4 * i + j;
		}
	}

	std::cout << matrix << std::endl;


	matrix = transposeMtx(matrix);

	std::cout << matrix << std::endl;

	return 0;
}

