


#include <iostream>
#include <string>
#include <loki/TypeManip.h>
#include <loki/HierarchyGenerators.h>


template<typename Type>
class Interface {
public:
	void setData(const Type& value) throw() {
		std::cerr << typeid(value).name() << std::endl;
	}
};


template<typename TypeList, template<typename> class Interfacer>
class Main
	: public ::Loki::GenScatterHierarchy<TypeList, Interfacer>
{
public:
	template<typename Type>
	void setData(const Type& value) throw() {
		this->Interfacer<Type>::setData(value);
	}
};

typedef LOKI_TYPELIST_3(int, double, std::string) TYPELIST;


int main() {
	Main<TYPELIST, Interface> obj;
	obj.setData(std::string("test"));
}


