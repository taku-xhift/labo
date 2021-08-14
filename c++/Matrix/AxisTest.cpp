

#include <d3dx9.h>
#include <d3d9.h>

#include <iostream>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>


typedef boost::numeric::ublas::vector<float>  Vector3;
typedef boost::numeric::ublas::matrix<float>  Matrix44;


int main()
{
	Vector3  vector(4);
	Matrix44 matrix(4, 4);
	D3DXVECTOR3 dVector3;
	D3DXMATRIX dMatrix44;

	for (int i = 0; i < vector.size(); ++i) {
		vector(i) = i;
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix(i, j) = 4 * i + j;
			dMatrix44.m[i][j] = matrix(i, j);
		}
	}

	std::cout << vector << std::endl;
	std::cout << matrix << std::endl;
	//std::cout << dMatrix44 << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << dMatrix44.m[i][j] << " ";
		}
	}
	std::cout << std::endl;

	Vector3 multipul = boost::numeric::ublas::prod(matrix, vector);
	//Vector3 multipul = boost::numeric::ublas::prod(vector, matrix);

	std::cout << multipul << std::endl;


	return 0;
}




