


#include <iostream>
#include <boost/any.hpp>


template <typename Collecter, typename Data>
bool setData(Collecter& collector_, Data data_, typename Collecter::requestDataType* = 0) {
	std::cout << "alone" << std::endl;
	bool result = true;
	try {
		collector_ = boost::any_cast<Collecter>(data_);
	} catch (boost::bad_any_cast& ) {
		std::cout << "ザンネン" << std::endl;
		result = false;
	}
	return result;
}


template <typename Collecter, typename Data>
bool setData(Collecter& collector_, Data data_) {
	std::cout << "with requestDataType" << std::endl;
	bool result = true;
	try {
		collector_.setData(boost::any_cast<Collecter::requestDataType>(data_));
	} catch (boost::bad_any_cast& ) {
		std::cout << "ザンネン" << std::endl;
		result = false;
	}
	return result;
}

class Data {
public:

	Data(int integer_ = 0) : integer(integer_) {}

	int integer;
};

class Base {
	
};

class Test : public Base{
public:
	typedef Data requestDataType;

	void setData(Data data_) { this->data = data_; }

//private:

	Data data;
};

int main() {

	boost::any data = Data(23);
	//boost::any data = 3;

	//Base* test = new Test();
	Test test;

	std::cout << "setData(test, data) = " << setData(test, data) << std::endl;
	std::cout << test.data.integer << std::endl;

	data = 2;
	int integer = 0;

	std::cout << "setData(integer, data) = " << setData(integer, data) << std::endl;
	std::cout << integer << std::endl;
}


