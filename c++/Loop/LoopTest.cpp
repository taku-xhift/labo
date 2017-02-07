

#include <iostream>
#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/mem_fn.hpp>

typedef boost::numeric::ublas::vector<float> Vector3;

class Test2
{
public:

	Vector3 position;

	Test2() : position(3)
	{
		this->position(0) = this->position(1) = this->position(2) = .0f;
	}

	void setPosition(Vector3 position_)
	{
		this->position = position_;
	}
};
typedef boost::shared_ptr<Test2> SpTest2;


class Test
{
public:

	std::list<SpTest2>  vectorList;

	Test()
	{
	}

	void setPosition(Vector3 vector)
	{
		std::for_each(this->vectorList.begin(),
			this->vectorList.end(),
			boost::bind(boost::mem_fn(&Test2::setPosition), vector));
			//bind2nd(boost::mem_fn(&Test2::setPosition), vector));
			//bind2nd(mem_fun_ref(&SpTest2::get().setPosition), vector));
	}
};

class Out
{
public:
	void operator() (SpTest2 test2)
	{
		std::cout << test2->position << std::endl;
	}
};



int main()
{
	Test test;

	for (int i = 0; i < 10; ++i) {
		SpTest2 test2(new Test2());
		test.vectorList.push_back(test2);
	}

	Vector3 position(3);
	position(0) = 1.0f; position(1) = 2.0f; position(2) = 3.0f;
	test.setPosition(position);

	for_each(test.vectorList.begin(), test.vectorList.end(), Out());

	return 0;
}

