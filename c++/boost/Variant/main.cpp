



#include <iostream>
#include <string>
#include <boost/variant.hpp>

class Test1 {
public:
	int integer;
};

class Test2 {
public:
	int integer;
};

template <typename V> void print(V& variant_) {
	if (int* pi = boost::get<int>(&variant_)) {
		std::cout << "これは int 型です： " << *pi << std::endl;
	} else if (std::string* ps = boost::get<std::string>(&variant_)) {
		std::cout << "これは string 型です： " << *ps << std::endl;
	} else if (double* pd = boost::get<double>(&variant_)) {
		std::cout << "これは double 型です： " << *pd << std::endl;
	}

	std::cout << "一仕事終わりました" << std::endl;
}


class print_visitor
	: public boost::static_visitor<void> {
public:
	void operator()(int& i) const {
		std::cout << "これは int です：" << i << std::endl;
	}
	void operator()(std::string& s) const {
		std::cout << "これは string です：" << s << std::endl;
	}
	void operator()(double& d) const {
		std::cout << "これは double です：" << d << std::endl;
	}
	void operator()(Test1& test1) const {
		std::cout << "これは test1 です：" << test1.integer << std::endl;
	}
	void operator()(Test2& test2) const {
		std::cout << "これは test2 です：" << test2.integer << std::endl;
	}
};

int main() {
//	boost::variant<int, std::string, double, char> myFirstVariant("こんにちは！");
//	print(myFirstVariant);
//	myFirstVariant = 12;
//	print(myFirstVariant);
//	myFirstVariant = 1.1;
//	print(myFirstVariant);
//	myFirstVariant = 'a';
//	print(myFirstVariant);

	boost::variant<int, std::string, double, Test1, Test2> myFirstVariant("こんにちは！");
	print_visitor v;

	boost::apply_visitor(v, myFirstVariant);
	myFirstVariant = 12;
	boost::apply_visitor(v, myFirstVariant);
	myFirstVariant = 1.1;
	boost::apply_visitor(v, myFirstVariant);
	myFirstVariant = Test1();
	boost::apply_visitor(v, myFirstVariant);
	myFirstVariant = Test2();
	boost::apply_visitor(v, myFirstVariant);
}


