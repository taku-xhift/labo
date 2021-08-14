

#include <iostream>
#include <typeinfo>
#include <string>

//using namespace std;

template<class Type>
class Base
{
public:
	virtual void Test(){}
	Type a;
};

template<class Type>
class Deriv : public Base<Type>
{
public:
	virtual void Test(){}
	Type b;
};

void main()
{
	Deriv<int>   intD;
	Deriv<char>  charD;
	std::string  string;

	std::cout << "intD :" << typeid(intD) .name() << std::endl;
	std::cout << "charD:" << typeid(charD).name() << std::endl;
	std::cout << ( typeid(intD) == typeid(charD) ? "true" : "false" ) << std::endl;
	std::cout << "intD :" << typeid(string) .name() << std::endl;
	std::cout << ( typeid(string) == typeid(std::string) ? "true" : "false" ) << std::endl;
}
