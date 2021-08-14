


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


template<class T, template<class> class ComparePolicy>
class SortedVector
{
private:

	std::vector<T> vec_;

public:

	void push_back(const T& value)
	{
		vec_.push_back(value);
		std::sort(vec_.begin(), vec_.end(), &ComparePolicy<T>::compare);
	}

	void disp() const
	{
		std::copy(vec_.begin(), vec_.end(), std::ostream_iterator<T>(std::cout, "\n"));
	}
};


template<class T>
struct LessPolicy
{
	static bool compare(const T& lhs, const T& rhs)
	{
		return lhs < rhs;
	}
};


template<class T>
struct GraterPolicy
{
	static bool compare(const T& lhs, const T& rhs)
	{
		return lhs > rhs;
	}
};


class Monster
{
	friend std::ostream& operator<<(std::ostream& os, const Monster& monster);

	int number;
	std::string name;

public:

	Monster(int number_, std::string name_)
		: number(number_)
		, name(name_)
	{
		
	}

	int getNumber() const
	{
		return this->number;
	}

};

bool operator < (const Monster& lhs, const Monster& rhs)
{
	return lhs.getNumber() < rhs.getNumber();
}

bool operator > (const Monster& lhs, const Monster& rhs)
{
	return lhs.getNumber() > rhs.getNumber();
}


// 出力用の<<演算子定義
std::ostream& operator<<(std::ostream& os, const Monster& monster)
{
	os << monster.name;
	return os;
}


int main()
{
	SortedVector<Monster, LessPolicy> v;

	Monster monster(1, "gobline");
	Monster monster2(0, "slime");
	Monster monster3(45, "satern");

	v.push_back(monster);
	v.push_back(monster2);
	v.push_back(monster3);

	v.disp();
}




