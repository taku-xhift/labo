


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
		std::cout << this->age_ << "歳の" << this->name_ << std::endl;
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
	animal a1("猿", 3);
	animal a2("熊", 8);
	animal a3("亀", 56);
	animal a4("猿", 5);

	std::set<animal> s;
	s.insert(a1);
	s.insert(a2);
	s.insert(a3);
	s.insert(a4);

	std::cout << "動物の数：" << s.size() << std::endl;
	std::for_each(s.begin(), s.end(), boost::bind(&animal::print, _1));
	std::cout << std::endl;

	std::set<animal>::iterator it(s.find(animal("猿", 200)));

	if (it != s.end()) {
		std::cout << "なんと凄いことに、この set には 200 歳の猿がいる！" << std::endl;
		it->print();
	}

	it = std::find(s.begin(), s.end(), animal("猿", 200));

	if (it == s.end()) {
		std::cout << "当たり前のことだが、この set には 200 歳の猿なんていない！" << std::endl;
	};

	return 0;
};


