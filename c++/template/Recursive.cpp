


#include <iostream>


template<typename T>
class Base
	// : public T
{
public:
	typedef typename T::DataType Data;

	virtual ~Base() {
	}

	Data& GetData() {
		return this->data_;
	}

private:
	Data data_;
};


class Sample {
public:
	int integer_;
};


class Screen
	: public Base<Screen>
{
public:
	typedef Sample DataType;

	void Print() {
		std::cout << this->GetData().integer_ << std::endl;
	}
};


int main() {
	Screen screen;
	screen.Print();
}


