

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/format.hpp>

typedef boost::numeric::ublas::matrix<float> Matrix44;


void Out(const char *const message)
{
	
}


int main()
{
	Matrix44 matrix = boost::numeric::ublas::identity_matrix<float> (4);

	Out(std::cout << matrix);
	//std::cout << matrix << std::endl;

	return 0;
}


