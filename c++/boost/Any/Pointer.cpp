


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>


class A {
public:
	virtual ~A() {
		std::cout << "A::~A()" << std::endl;
	}

	virtual void not_virtual() {
		std::cout << "A::not_virtual()" << std::endl;
	}

	virtual void is_virtual() {
		std::cout << "A::is_virtual()" << std::endl;
	}
};


class B
	: public A {
public:
	~B() {
		std::cout << "B::~B()" << std::endl;
	}

	void not_virtual() {
		std::cout << "B::not_virtual()" << std::endl;
	}

	virtual void is_virtual() {
		std::cout << "B::is_virtual()" << std::endl;
	}
};


void foo(boost::any& any_) {
	std::cout << std::endl;

	// boost::shared_ptr<A> かどうかをテストする
	try {
		boost::shared_ptr<A> ptr = boost::any_cast<boost::shared_ptr<A> >(any_);
		std::cout << "この any には boost::shared_ptr<A> が格納されています" << std::endl;
		ptr->is_virtual();
		ptr->not_virtual();
		return;
	} catch (boost::bad_any_cast& e) {
		
	}

	// boost::shared_ptr<B> かどうかをテストする
	try {
		boost::shared_ptr<B> ptr = boost::any_cast<boost::shared_ptr<B> >(any_);
		std::cout << "この any には boost::shared_ptr<B> が格納されています" << std::endl;
		ptr->is_virtual();
		ptr->not_virtual();
		return;
	} catch (boost::bad_any_cast& e) {
		
	}

	std::cout << "この any には、本関数が必要とする値は保持されていません！" << std::endl;
}


int main() {
	std::cout << "any と shared_ptr の使用例" << std::endl;

	boost::any a1(boost::shared_ptr<A>(new A));
	boost::any a2(std::string("ただの文字列"));

	{
		boost::any b1(boost::shared_ptr<A>(new B));
		boost::any b2(boost::shared_ptr<B>(new B));
		std::vector<boost::any> vec;
		vec.push_back(a1);
		vec.push_back(a2);
		vec.push_back(b1);
		vec.push_back(b2);

		std::for_each(vec.begin(), vec.end(), foo);
		std::cout << std::endl;
	}

	std::cout << "b1 と b2 は破棄されたため、該当 shared_ptr の参照カウントはゼロになりました" << std::endl;

}


