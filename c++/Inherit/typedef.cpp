


#include <iostream>
#include <string>
#include <typeinfo>


#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>


template<typename T>
struct has_setData : boost::mpl::false_ {};

template <typename T, typename U>
void setData(T& t, U& u, boost::mpl::true_ const& dummy)
{
	t.setData(u);
}

template <typename T, typename U>
void setData(T& t, U& u, boost::mpl::false_ const& dummy)
{
	std::cout << typeid(T).name() << " does not have setData\n";
}

template <typename T, typename U>
void setData(T& t, U& u) { setData(t,u, has_setData<T>()); }


//template<typename T, typename U>
//typename boost::enable_if<has_setData<T> >::type setData(T& t, U& u)
//{
//	std::cout << "settted" << std::endl;
//}

class Interface {
public:
	virtual void setData(int integer) {
	}
};

class Base {
public:
	typedef int require;

	virtual std::string getName() const = 0;

	void setData(const require& value_) {
		std::cout << "setted data" << std::endl;
	}
};


template<typename Policy>
class Delived
	: public Policy
	, public Interface
{
public:
//	typedef std::string require;

	std::string getName() const {
		return std::string();//typeid(require).name();
	}
};


int main() {
//	std::cout << typeid(Base::require).name() << std::endl;
	std::cout << typeid(Delived<Base>::require).name() << std::endl;
	__if_exists(Delived<Base>::setData) {
		std::cout << "exists" << std::endl;
	}
	Delived<Base> obj;
	//obj.setData(1);
	int integer = 12;
	//setData(obj, integer);
	//Base* base = new Delived();
	//std::cout << base->getName() << std::endl;
}


