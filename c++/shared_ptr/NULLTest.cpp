
// ����ꂽ���_

// boost::shared_ptr �͐錾�������_�ł�NULL�|�C���^�̗l�q�B
// �Ȃ̂ŁA�錾���������Ŏ��Ԃ����邩�̂悤�Ɋ��Ⴂ���Ȃ����ƁB
// �����܂ł���̓|�C���^�Ȃ̂��B




#include <iostream>
#include <boost/shared_ptr.hpp>

class Test
{
public:
	boost::shared_ptr<int> number;
};

int main()
{
	//::boost::shared_ptr<Test> test(new Test());
	Test test;


	if (test.number != NULL) {
		::std::cerr << "Test is Here!" << ::std::endl;
	}


	return 0;
}


