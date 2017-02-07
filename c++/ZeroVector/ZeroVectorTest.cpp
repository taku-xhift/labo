

#include <boost/numeric/ublas/vector.hpp>
#include <iostream>
#include <boost/numeric/ublas/io.hpp>


int main()
{
	boost::numeric::ublas::vector<float> vector(3);
	vector = boost::numeric::ublas::zero_vector<float> ();

	std::cerr << vector << std::endl;

	return 0;
}


