


#include <iostream>
#include <list>

class Base
{
public:

	int baseID;
};


class Child
{
public:

	int childID;
};


static std::list<Base&> baseList;

Base getBase()
{
	static int objectID = 0;
	++objectID;
	Base base = objectID;

	baseList.push_back(base);

	return base;
}



int main()
{
	

	return 0;
}

