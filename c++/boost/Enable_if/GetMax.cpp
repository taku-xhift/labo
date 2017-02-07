


#include <iostream>
#include <limits>
#include <string>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>


//template <typename T>
//class some_class
//{
//public:
//	int max() const {
//		std::cout << "some_class::max() for the primary template" << std::endl;
//		return std::numeric_limits<int>::max();
//	}
//};

template <typename T, typename Enable = void>
class some_class
{
public:
	int max() const {
		std::cout << "プライマリテンプレートの some_class::max() : " << std::endl;
		return std::numeric_limits<int>::max();
	}
};


template <typename T>
class some_class<T, typename boost::enable_if<boost::is_arithmetic<T> >::type>
{
public:
	T max() const {
		std::cout << "算術型を伴うクラスの some_class::max() : " << std::endl;
		return std::numeric_limits<T>::max();
	}
};



int main() {
	std::cout << "std::string の最大値：" << some_class<std::string>().max() << std::endl;
	std::cout << "void の最大値：" << some_class<void>().max() << std::endl;
	std::cout << "short の最大値：" << some_class<short>().max() << std::endl;
	std::cout << "int の最大値：" << some_class<int>().max() << std::endl;
	std::cout << "long の最大値：" << some_class<long>().max() << std::endl;
	std::cout << "double の最大値：" << some_class<double>().max() << std::endl;

	return 0;
}

