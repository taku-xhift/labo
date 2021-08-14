


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
		std::cout << "�v���C�}���e���v���[�g�� some_class::max() : " << std::endl;
		return std::numeric_limits<int>::max();
	}
};


template <typename T>
class some_class<T, typename boost::enable_if<boost::is_arithmetic<T> >::type>
{
public:
	T max() const {
		std::cout << "�Z�p�^�𔺂��N���X�� some_class::max() : " << std::endl;
		return std::numeric_limits<T>::max();
	}
};



int main() {
	std::cout << "std::string �̍ő�l�F" << some_class<std::string>().max() << std::endl;
	std::cout << "void �̍ő�l�F" << some_class<void>().max() << std::endl;
	std::cout << "short �̍ő�l�F" << some_class<short>().max() << std::endl;
	std::cout << "int �̍ő�l�F" << some_class<int>().max() << std::endl;
	std::cout << "long �̍ő�l�F" << some_class<long>().max() << std::endl;
	std::cout << "double �̍ő�l�F" << some_class<double>().max() << std::endl;

	return 0;
}

