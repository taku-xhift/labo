


#include <iostream>
#include <boost/any.hpp>
#include <vector>


class Base {
public:

	virtual void save(const boost::any& any) throw() = 0;

	template<typename ValueType>
	void sendData(const ValueType& value) throw() {
		this->save(boost::any(value));
	}
};


class Derive : public Base {
public:
	void save(const boost::any& any) throw() {
		this->container_.push_back(any);
	}

	std::vector<boost::any> container_;
};


int main() {
	Base* derive = new Derive();

	derive->sendData(6);
	std::cerr << boost::any_cast<int>(dynamic_cast<Derive*>(derive)->container_.front()) << std::endl;
}


