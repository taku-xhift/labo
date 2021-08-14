

#include <iostream>
#include <cassert>



class Base
{
public:

	//virtual ~Base {}

	virtual int getInt() = 0;

	int integer;
};



class Child1 : public Base {
public:

	Child1() { this->integer = 1; }

	int getInt() { return this->integer; }
};

class Child2 : public Base {
public:

	Child2() { this->integer = 2; }

	int getInt() { return this->integer;}
};


Base* creater(int num_) {
	switch (num_) {
        case 1: {
		    return new Child1();
		}
        case 2: {
		    return new Child2();
    	}
	    default: {
		    //return new Base();
			assert(0);
		}
	}
}


int main()
{
	Base* base = creater(2);

	std::cout << base->integer << std::endl;

	return 0;
}

