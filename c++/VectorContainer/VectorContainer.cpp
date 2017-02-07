

#include <iostream>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::vector<float> Vector3;

int main()
{
	std::vector< std::vector<Vector3> > vertexContainer;

	for (int j = 0; j < 4; ++j) {
		std::vector<Vector3> container;
		for (int i = 0; i < 12; ++i) {
			Vector3 vector(3);
			vector(0) = vector(1) = vector(2) = i;
			container.push_back(vector);
		}
		vertexContainer.push_back(container);
	}

	for (int i = 0; i < vertexContainer.size(); ++i) {
		for (int j = 0; j < vertexContainer[i].size(); ++j) {
			std::cout << vertexContainer[i][j++] << std::endl;
			std::cout << vertexContainer[i][j++] << std::endl;
			std::cout << vertexContainer[i][j] << std::endl;
		}
	}

	vertexContainer.erase();

	std::cout << vertexContainer.remove() << std::endl;

	return 0;
}

