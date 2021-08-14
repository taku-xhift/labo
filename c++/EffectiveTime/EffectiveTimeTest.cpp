#include <iostream>

#include <boost/shared_ptr.hpp>

#include <boost/numeric/ublas/vector.hpp>


typedef boost::numeric::ublas::vector<float> Vector3;
typedef boost::shared_ptr<Vector3> SpVector3;



class Test
{
public:
	Test() : pos(3)
	{
		pos(0) = pos(1) = pos(2) = .0f;
	}

	void Add(Vector3 translation)
	{
		pos += translation;
	}

	Vector3 pos;
};

typedef boost::shared_ptr<Test> SpTest;




class Sample
{
public:
	Sample()
	{
		SpTest test(new Test());
		this->spTest = test;
	}

	SpTest getTest()    { return this->spTest; }

	SpTest spTest;
};


int main()
{
	Sample sample;

	Vector3 vec(3);
	vec(0) = vec(1) = vec(2) = 2.0f;


	sample.getTest()->Add(vec);

	std::cout << sample.spTest->pos(0) << std::endl;


	return 0;
}

