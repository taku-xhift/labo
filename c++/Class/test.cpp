#include <iostream>

class Base
{
public:
	Base()  : mass(4.0f) {};
	float getMass()
	{
		return this->mass;
	}

private:
	float mass;
};

class Child    :  public Base
{
};

int main()
{
	Child child;
	std::cout << child.getMass() << std::endl;
	return 0;
};

