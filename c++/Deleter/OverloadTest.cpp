
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------
//  define
//-----------------------------------------------------




/**
 * @brief 
 *          
 * @author  Takuya Shishido
 * @date    2009.11.25 11:33:07
 * @version 0.01, Shishido Takuya, 2009.11.25 11:33:07
 */
class ManagedDeleter
{
public:

	void operator() (void* data)
	{
		std::cout << "Managed Deleter is called." << std::endl;
		std::cout << (unsigned int)(data) << std::endl;
	}

private:


};    // class ManagedDeleter


class Test
{
public:

	int integer;

	Test()
		: integer(3)
	{
		std::cout << this->integer << std::endl;
	}
};


int main()
{
	{
		boost::shared_ptr<Test> test(new Test(), ManagedDeleter());
	}

	return 0;
}



