


#include <iostream>


class Data {
public:

	Data(int integer = INT_MAX) throw()
		: integer_(integer)
	{
		
	}

	explicit Data(const Data& other) throw()
		: integer_(other.integer_)
	{
	}

	Data& operator=(const Data& other) throw() {
		this->integer_ = other.integer_;
	}

	int integer_;
};


class Test {
public:

	Test(const Data& data) throw()
		: data_(new Data(data))
	{}

	void set(const Data& data) throw()
	{
		this->data_ = new Data(data);
	}

	Data* data_;
};



int main() {
	Data data(99);
	Test test(data);

	{
		Data data(3);
		test.set(data);
	}

	std::cout << test.data_->integer_ << std::endl;
}


