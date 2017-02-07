


#include <iostream>
#include <cassert>
#include <boost/any.hpp>
#include <vector>


template<typename Pointer>
class DataBase {
public:

	DataBase(const Pointer& pointer) throw()
		: pointer_(new Pointer(pointer))
	{
		
	}

	void set(Pointer* pointer) throw() {
		if (pointer == NULL) { assert(0); }

		this->pointer_ = pointer;
	}

	Pointer* pointer_;
};



class Data1 {};
class Data2 {};
class Data3 {};



class Global {
public:

	static Global getInstance() throw() {
		static Global this_;
		return this_;
	}

	std::vector<boost::any> dataList_;
};


int main() {
	Data1 data1;
	Data2 data2;
	Global::getInstance().dataList_.push_back(DataBase<Data1>(data1));

	Global::getInstance().dataList_.at(0).set(&data2);
}

