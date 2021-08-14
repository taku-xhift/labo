#include <map>
#include <iostream>
#include <string>
#include <vector>



//! \brief    �L�[�̉�����Ԃ��`�F�b�N���邽�߂̃��X�g
enum KeyState
{
	KEYSTATE_NONE    = 0,    //!< �����ĂȂ�
	KEYSTATE_RELEASE = 1,    //!< �������u��
	KEYSTATE_PUSH    = 2,    //!< �������u��
	KEYSTATE_KEEP    = 4,    //!< ���������Ă���
};


//! \brief    �L�[�̏�Ԃ��Ǘ����邽�߂̍\����
struct KeyParameter
{
	KeyState	keyState;	//<! ���
	float		keyValue;	//<! ���݂̒l
	float		keepTime;	//<! �����������Ă��鎞��
	float		pushTime;	//<! ����������

	KeyParameter():keyState(KEYSTATE_NONE),keyValue(0),keepTime(0),pushTime(0){}
};



int main()
{
	::std::map<::std::string, ::std::vector<int>> mapTest;


	mapTest.insert(::std::map<::std::string, ::std::vector<int>>::value_type( "aaa", 10));
	mapTest.insert(::std::map<::std::string, ::std::vector<int>>::value_type("aaa", 30));

	::std::map<::std::string, ::std::vector<int>>::iterator mapIterator = mapTest.begin();
	while (mapIterator != mapTest.end()) {
		::std::cout << (*mapIterator).first << ":" << (*mapIterator).second << ::std::endl;
		++mapIterator;
	}

	std::cerr << mapTest["aaa"] << std::endl;
	std::cerr << mapTest["bbb"] << std::endl;

	::std::map<::std::string, ::std::vector<int>>::iterator mapIte = mapTest.find("aaa");
	for (size_t i = 0; i < mapIte->second.size(); ++i) {
		std::cerr << (*mapIte).second() << std::endl;
	}

	return 0;
}