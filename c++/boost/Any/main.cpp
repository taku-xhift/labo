

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <boost/any.hpp>



class A {
public:
	void some_function() {
		std::cout << "A::some_function()" << std::endl;
	}
};

class B {
public:
	void some_function() {
		std::cout<< "B::some_function()" << std::endl;
	}
};


class C {
public:
	void some_function() {
		std::cout << "C::some_function()" << std::endl;
	}
};



void print_any(boost::any& any_) {
	if (A* pA = boost::any_cast<A>(&any_)) {
		pA->some_function();
	} else if (B* pB = boost::any_cast<B>(&any_)) {
		pB->some_function();
	} else if (C* pC = boost::any_cast<C>(&any_)) {
		pC->some_function();
	} else {
		try {
			std::cout << boost::any_cast<std::string>(any_) << std::endl;
		} catch (boost::bad_any_cast&) {
			std::cout << "おっと！" << std::endl;
		}
	}
}


int main() {

	std::vector<boost::any> store_anything;

	store_anything.push_back(A());
	store_anything.push_back(B());
	store_anything.push_back(C());

	// 追加のオブジェクト
	store_anything.push_back(std::string("これは素晴らしい！"));
	store_anything.push_back(3);
	store_anything.push_back(std::make_pair(true, 7.92));

	void print_any(boost::any& a);

	std::for_each(store_anything.begin(), store_anything.end(), print_any);

	return 0;
}


