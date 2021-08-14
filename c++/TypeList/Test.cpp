


#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <loki/Typelist.h>
#include <loki/HierarchyGenerators.h>
#include <loki/TypeManip.h>


template<typename Type>
class AbstructPrinter {
public:
	virtual void printBase(const Type& type) const throw() {
		std::cerr << typeid(type).name() << std::endl;
	}
};

template<typename TList,
         template<typename> class Unit = AbstructPrinter>
class Printer : public Loki::GenScatterHierarchy<TList, Unit>
{
public:
	typedef TList PrinterList;
	template<typename ValueType>
	void print(const ValueType& value) const throw() {
		const Unit<ValueType>& unit = *this;
		unit.printBase(value);
		//this->printBase(Loki::Type2Type<ValueType>(), value);
		std::cout << __FUNCTION__ << std::endl;
	}
};


typedef Printer<Loki::TL::MakeTypelist<std::vector<int>, std::string>::Result> TypeNamePrinter;

void main() {
	//TypeNamePrinter printer;
	//printer.print(4.0f);
	std::cout << typeid(TypeNamePrinter).name() << std::endl;
}


