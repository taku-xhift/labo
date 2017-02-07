


#include <iostream>
#include <vector>


template<bool B, typename T = void>
struct enable_if_c {
	typedef T type;
};
template<typename T>
struct enable_if_c<false, T> {};

template<typename Cond, typename T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};




template<bool B, typename T = void>
struct disable_if_c {
	typedef T type;
};

template<typename T>
struct disable_if_c<true, T> {};

template<typename Cond, typename T = void>
struct disable_if : public disable_if_c<Cond::value, T> {};





template<typename T>
class has_iterator {
	typedef char yes;
	typedef struct { char a[2]; } no;

	template<typename U>
	static yes test(typename U::iterator*);

	template<typename U>
	static no test(...);
public:
	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template<typename T>
class has_setData {
	typedef char yes;
	typedef struct { char a[2]; } no;

	template<typename U>
	static yes test(typename U::set_Data*);

	template<typename U>
	static no test(...);
public:
	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};



class Data {
public:
	Data(int integer_ = 0) : integer(integer_) {}

	int integer;
};

class Test {
public:
	typedef void (*set_Data)(Data&);

	void setData(Data& data_) { this->data = data_; }
	Data data;
};

class Sample {
public:
	Data data;
};


template<typename T>
void something(T& t_, Data& data_, typename enable_if<has_setData<T> >::type* = 0)
{
	std::cout << "Having value_type!!" << std::endl;
	t_.setData(data_);
	std::cout << t_.data.integer << std::endl;
}


template<typename T>
void something(T& t_, Data& data_, typename disable_if<has_setData<T> >::type* = 0)
{
	std::cout << "Another." << std::endl;
}



int main() {
	using namespace std;

	//cout << has_iterator<vector<int> >::value << endl;
	//cout << has_iterator<int>::value << endl;

	//cout << has_setData<Test>::value << endl;

	Test test;
	Sample sample;
	Data data; data.integer = 2;

	something(test, data);
	something(sample, data);
}


