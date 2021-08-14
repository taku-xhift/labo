


#include <iostream>
#include <boost/shared_ptr.hpp>



class HavokWorld
{
	float floating;
public:

	HavokWorld()    : floating(3.0f)
	{
	}

	void reset(float &floating_)
	{
		floating_ = this->floating;
	}
};
typedef boost::shared_ptr<HavokWorld> SpHavokWorld; 


class Test
{
public:

	Test()
	{
		std::cout << "Constructord a Test." << std::endl;
	}

	~Test()
	{
		std::cout << "Destructored a Test." << std::endl;
	}
};

typedef boost::shared_ptr<Test> SpTest;


class Deleter
{
public:

	template <typename T> void operator()(T *t, SpHavokWorld spHavokWorld)
	{
		std::cout << "Deleter is called." << spHavokWorld->floating << std::endl;
	}
};


class Test2
{
public:

	Test2(SpHavokWorld world)
	{
		
		//this->spTest.reset(new Test(), this->free(world));
		//this->spTest.reset(new Test(), this->free(world));
		//this->spTest.reset(new Test(), this->operator ()(world));
		//this->spTest.reset(new Test()
		SpTest test(new Test(), Deleter(world));
		std::cout << "Constructord a Test." << std::endl;
	}

	~Test2()
	{
		std::cout << "Destructored a Test." << std::endl;
	}


	void free(SpHavokWorld world)
	{
		world->reset(this->floating);
	}

	void free()
	{
	}

	void operator()(SpHavokWorld world)
	{
		world->reset(this->floating);
	}


	SpTest spTest;
	float floating;
};



int main()
{


	return 0;
}




