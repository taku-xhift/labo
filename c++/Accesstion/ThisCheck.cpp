#include <iostream>


class Super
{
public:
	const char* sName;

	Super()    : sName("superPrint")
	{
	}


	void accesstion()
	{
		::std::cerr << sName << ::std::endl;
	}

};


class Child    : public Super
{
public:
	const char* cName;


	Child()    : cName("ChildPrint")
	{
	}

	void accesstion()
	{
		::std::cerr << cName << ::std::endl;
	}

};





int main()
{
	Child child;

	child.accesstion();


	return 0;
}

