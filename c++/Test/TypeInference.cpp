


#include <iostream>
#include <boost/any.hpp>
#include <vector>
#include <stdexcept>


class Test {
public:
	int value_;
};


class Rapper {
public:
	Rapper() throw()
	{
		
	}

	template<typename ValueType>
	void add(const ValueType& value) throw(std::bad_alloc) {
		this->value_.push_back(boost::any(value));
	}

	template<typename To>
	operator To() const throw(boost::bad_any_cast) {
		for (std::vector<boost::any>::const_iterator ite = this->value_.begin(); ite != this->value_.end(); ++ite) {
			try {
				To temp = boost::any_cast<To>(*ite);
				return temp;
			} catch (boost::bad_any_cast& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}
private:
	std::vector<boost::any> value_;
};


int main() {
	Rapper container;

	int integer = 4;
	Test test;
	test.value_ = 45;

	container.add(test);
	container.add(integer);

	int value = container;
	std::cerr << value << std::endl;
	Test test2 = container;
	std::cerr << test2.value_ << std::endl;
}


