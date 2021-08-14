


#include <iostream>
#include <boost/shared_ptr.hpp>


class Base {
public:
	virtual ~Base() {}
};



template<typename Type>
class Derived
	: public Base {
public:
	Derived(const Type& value_) : value(value_) {}
	~Derived() {}

	Type getValue() const { return this->value; }
private:
	Type value;
};



class Test {
public:
	template<typename Type>
	Test(const Type& type_) {
		this->value = boost::shared_ptr<Base>(new Derived<Type>(type_));
	}

	~Test() {
	}

	boost::shared_ptr<Base> value;
};



class Data {
public:
	Data(int integer_ = 3) : integer(integer_) {}
	int integer;
};



int main() {
	Test test = Test(3);

	std::cout << reinterpret_cast<Derived<int>*>(test.value.get())->getValue() << std::endl;

	//Test test_data = Test(Data());

	//std::cout << test.value->integer << std::endl;

	return 0;
}

