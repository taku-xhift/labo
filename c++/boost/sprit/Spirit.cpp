

#include <string>
#include <boost/spirit/include/qi.hpp>

std::pair<std::string, std::string> parse( const std::string& string_, char separator_ )
{
	namespace qi = boost::spirit::qi;
	typedef std::pair<std::string, std::string> value_type;
	typedef qi::rule<std::string::const_iterator, std::string()> rule_type;

	const rule_type forwardRule = *(qi::char_ - separator_) >> separator_ >> qi::omit[*(qi::char_)];
	const rule_type backwardRule = qi::omit[*(qi::char_ - separator_)] >> separator_ >> *(qi::char_);

	value_type result;

	qi::parse(string_.begin(), string_.end(), forwardRule, result.first);
	qi::parse(string_.begin(), string_.end(), backwardRule, result.second);

	return result;
}

int main() {
	std::cout << parse("fdsa_acg_fdsa.png", '_').first << std::endl;
	std::cout << parse("fdsa_acg_fdsa.png", '_').second << std::endl;
}

