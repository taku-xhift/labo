


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/variant.hpp>


class stream_output_visitor
	: public boost::static_visitor<void> {
	std::ostream& os_;

public:

	stream_output_visitor(std::ostream& os) : os_(os) {}

	template <typename T>
	void operator()(T& t) const {
		this->os_ << t << std::endl;
	}
};


class lexicographical_visitor
	: public boost::static_visitor<bool> {
public:
	template <typename Lhs, typename Rhs>
	bool operator() (const Lhs& lhs, const Rhs& rhs) const {
		return get_string(lhs) < get_string(rhs);
	}

private:
	template<typename Type>
	static std::string get_string(const Type& type) {
		std::ostringstream s;
		s << type;
		return s.str();
	}

	static const std::string& get_string(const std::string& s) {
		return s;
	}
};


int main() {
	boost::variant<int, std::string> var1 = "100";
	boost::variant<double> var2 = 99.99;

	std::cout << "var < var2 : " << boost::apply_visitor(lexicographical_visitor(), var1, var2) << std::endl;

	typedef std::vector<boost::variant<int, std::string, double> > vec_type;

	vec_type vec;

	vec.push_back("‚±‚ñ‚É‚¿‚Í");
	vec.push_back(12);
	vec.push_back(1.12);
	vec.push_back("0");

	stream_output_visitor sv(std::cout);
	std::for_each(vec.begin(), vec.end(), sv);

	lexicographical_visitor lv;
	std::sort(vec.begin(), vec.end(), boost::apply_visitor(lv));

	std::cout << std::endl;
	std::for_each(vec.begin(), vec.end(), sv);
}


