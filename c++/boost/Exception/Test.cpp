#include <stdexcept>
#include <boost/exception/all.hpp>

// ��O�N���X�� boost::exception ���p�����Ē�`����Ɓc
class MyException
	: public boost::exception, public std::exception {};


int main() {
	std::cout << sizeof(MyException) << std::endl;
}
