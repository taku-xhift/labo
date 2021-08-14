
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


template <typename Func, typename T>
struct weak_ptr_unary_t : public std::unary_function<boost::weak_ptr<T>, bool>
{
	T t_;
	Func func_;

	weak_ptr_unary_t(const Func& func, const T& t)
		: t_(t), func_(func) {}

	bool operator() (boost::weak_ptr<T> arg) const {
		boost::shared_ptr<T> sp = arg.lock();
		if (!sp) {
			return false;
		}
		return func_(*sp, t_);
	}
};

template <typename Func, typename T> weak_ptr_unary_t<Func, T>
weak_ptr_unary(const Func& func, const T& value) {
	return weak_ptr_unary_t<Func, T>(func, value);
}


int main()
{
	std::vector<boost::weak_ptr<std::string> > vec;

	boost::shared_ptr<std::string> sp1(new std::string("スマートポイントと述語"));
	boost::shared_ptr<std::string> sp2(new std::string("の使用"));
	boost::shared_ptr<std::string> sp3(new std::string("例"));

	vec.push_back(boost::weak_ptr<std::string>(sp1));
	vec.push_back(boost::weak_ptr<std::string>(sp2));
	vec.push_back(boost::weak_ptr<std::string>(sp3));

	std::vector<boost::weak_ptr<std::string> >::iterator ite
		= std::find_if(vec.begin(), vec.end(), weak_ptr_unary(std::equal_to<std::string>(), std::string("の使用")));

	if (ite != vec.end()) {
		boost::shared_ptr<std::string> sp(*++ite);
		std::cout << *sp << std::endl;
	}

	return 0;
}
