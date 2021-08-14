


#include <boost/shared_ptr.hpp>
#include <iostream>


class Test
{
public:

	Test()   : integer(3)
	{
		std::cout << "Constructored a Test with integer = " << integer << std::endl;
	}

	~Test()
	{
		std::cout << "Destructored a Test." << std::endl;
	}

	void free()
	{
		std::cout << "Called Test::free()" << std::endl;
	}

	int integer;
};


class Free
{
public:
	template <typename T> void operator()(T *t)
	{
		t->free();
	}
};
	
	


//Attributes


//template <typename T>
class Deleter
{
public:
	//void operator()(T *t)
	template <typename T> void operator()(T *t)
	{
		std::cout << "Deleted in functor : Deleter." << std::endl;
		delete t;
		//delete test;
	}
};

//
//template <typename T>
//class TemplateTest
//{
//	//TemplateTest(T t)
//	void operator()(T *t)
//	{
//		std::cout << t << std::endl;
//	}
//};


int main()
{
	{
		boost::shared_ptr<Test> test(new Test(), Deleter());
	}

	{
		boost::shared_ptr<Test> test(new Test(), Free());
	}

	return 0;
}



