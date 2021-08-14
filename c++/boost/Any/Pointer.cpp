


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

	// boost::shared_ptr<A> ���ǂ������e�X�g����
	try {
		boost::shared_ptr<A> ptr = boost::any_cast<boost::shared_ptr<A> >(any_);
		std::cout << "���� any �ɂ� boost::shared_ptr<A> ���i�[����Ă��܂�" << std::endl;
		ptr->is_virtual();
		ptr->not_virtual();
		return;
	} catch (boost::bad_any_cast& e) {
		
	}

	// boost::shared_ptr<B> ���ǂ������e�X�g����
	try {
		boost::shared_ptr<B> ptr = boost::any_cast<boost::shared_ptr<B> >(any_);
		std::cout << "���� any �ɂ� boost::shared_ptr<B> ���i�[����Ă��܂�" << std::endl;
		ptr->is_virtual();
		ptr->not_virtual();
		return;
	} catch (boost::bad_any_cast& e) {
		
	}

	std::cout << "���� any �ɂ́A�{�֐����K�v�Ƃ���l�͕ێ�����Ă��܂���I" << std::endl;
}


int main() {
	std::cout << "any �� shared_ptr �̎g�p��" << std::endl;

	boost::any a1(boost::shared_ptr<A>(new A));
	boost::any a2(std::string("�����̕�����"));

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

	std::cout << "b1 �� b2 �͔j�����ꂽ���߁A�Y�� shared_ptr �̎Q�ƃJ�E���g�̓[���ɂȂ�܂���" << std::endl;

}


