


#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <boost/operators.hpp>
#include <boost/bind.hpp>

class animal : boost::less_than_comparable<animal, boost::equality_comparable<animal> >
{
	std::string    name_;
	int             age_;

public:
	animal(const std::string& name, int age) : name_(name), age_(age) {}

	void print() const {
		std::cout << this->age_ << "�΂�" << this->name_ << std::endl;
	};

	friend bool operator< (const animal& lhs, const animal& rhs) {
		return lhs.name_ < rhs.name_;
	};

	friend bool operator== (const animal& lhs, const animal& rhs) {
		return lhs.name_ == rhs.name_ && lhs.age_ == rhs.age_;
	}
};


int main()
{
	animal a1("��", 3);
	animal a2("�F", 8);
	animal a3("�T", 56);
	animal a4("��", 5);

	std::set<animal> s;
	s.insert(a1);
	s.insert(a2);
	s.insert(a3);
	s.insert(a4);

	std::cout << "�����̐��F" << s.size() << std::endl;
	std::for_each(s.begin(), s.end(), boost::bind(&animal::print, _1));
	std::cout << std::endl;

	std::set<animal>::iterator it(s.find(animal("��", 200)));

	if (it != s.end()) {
		std::cout << "�Ȃ�Ɛ������ƂɁA���� set �ɂ� 200 �΂̉�������I" << std::endl;
		it->print();
	}

	it = std::find(s.begin(), s.end(), animal("��", 200));

	if (it == s.end()) {
		std::cout << "������O�̂��Ƃ����A���� set �ɂ� 200 �΂̉��Ȃ�Ă��Ȃ��I" << std::endl;
	};

	return 0;
};


