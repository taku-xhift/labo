#include <map>
#include <iostream>
#include <string>
#include <vector>



//! \brief    キーの押下状態をチェックするためのリスト
enum KeyState
{
	KEYSTATE_NONE    = 0,    //!< 押してない
	KEYSTATE_RELEASE = 1,    //!< 離した瞬間
	KEYSTATE_PUSH    = 2,    //!< 押した瞬間
	KEYSTATE_KEEP    = 4,    //!< 押し続けている
};


//! \brief    キーの状態を管理するための構造体
struct KeyParameter
{
	KeyState	keyState;	//<! 状態
	float		keyValue;	//<! 現在の値
	float		keepTime;	//<! 押し続けいている時間
	float		pushTime;	//<! 押した時間

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