
#include <iostream>
#include <list>
//#include <algorithm>


#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/bind.hpp>
//#include <boost/mem_fn.hpp>
//#include <boost/bind/apply.hpp>

typedef boost::numeric::ublas::vector<float> Vector3;


class Test
{
public:

	Vector3 position;

	Test()
		: position(3)
	{
		this->position(0) = 1.0f;
		this->position(1) = 1.0f;
		this->position(2) = 1.0f;
	}

	void setPosition(Vector3 position_)
	{
		this->position = position_;
	}

	void translate(int num, Vector3 position_)
	{
		this->position = position_;
		std::cout << num << std::endl;
	}

	void out()
	{
		std::cout << "Called Test::out." << std::endl;
		std::cout << this->position << "\n" << std::endl;
	}
};
typedef boost::shared_ptr<Test> SpTest;


class Test2
{
public:

	std::list<SpTest> testList;
	//std::list<Test> testList;


	void setPosition(Vector3 position_)
	{
		Vector3 position(3);
		position(0) = 2.0f;
		position(1) = 3.0f;
		position(2) = 4.0f;

		for_each(this->testList.begin(),
			this->testList.end(),
			boost::bind(&Test::setPosition, _1, position_));
			//boost::bind(&Test::out, _1));
			//boost::bind(&Test::setPosition, 4, _1, position_));
			//boost::mem_fn(&Test::out));
			//boost::mem_fn(&Test::setPosition(position_)));
			//boost::bind(mem_fun_ref(&Test::setPosition), position_));			
			//boost::mem_fn(&Test::setPosition(position_)));			
			//boost::bind(&Test::setPosition, position_));
			//boost::bind(boost::apply<void>(), _1, position_));
			//bind2nd(boost::mem_fn(&Test::setPosition), position_));
	}

};

struct Out
{
	void operator() (SpTest test)
	{
		std::cout << test->position << std::endl;
	}
};


int main()
{
	Test2 test2;

	for (int i = 0; i < 10; ++i) {
		//Test test;
		SpTest test(new Test());
		test2.testList.push_back(test);
	}

	{
		Vector3 position(3);
		position(0) = 2.0f;
		position(1) = 3.0f;
		position(2) = 4.0f;

		test2.setPosition(position);
	}

	for_each(test2.testList.begin(),
		test2.testList.end(),
		Out());

	return 0;
}

