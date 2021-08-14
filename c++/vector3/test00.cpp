#include <iostream>
//#include <boost/numeric/ublas/vector.hpp>
using namespace std;

//typedef boost::numeric::ublas::vector<float> vector3;

class vector3
{
	union
	{
		boost::numeric::ublas::vector<float> val;

		struct
		{
			float x, y, z;
		};
	};

	vector3()    : val(3)
	{
	}

	~vector3()
	{
	}
};


int main()
{
	//vector3 vec;

	


	return 0;
}

