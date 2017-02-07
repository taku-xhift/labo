/**
 * @file
 * @brief メモリ管理練習
 *
 * @author Takuya Shishido
 * @date 2009.11.18 16:12:13
 *
 * @version 0.01, Shishido Takuya, 2009.11.18 16:12:13
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/



//---------------------------------------------------------
//  Include
//---------------------------------------------------------
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
//#include <boost/functional.hpp>
#include <boost/shared_ptr.hpp>
#include <new>

#include <crtdbg.h>
/**--------------------------------------------------------
 * @brief メモリデータ管理クラス
 * @author  Takuya Shishido
 * @date    2009/11/18 17:27
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
struct MemoryData
{
private:

	friend class PointerEqual;
	friend class ManagedDeleter;
	friend void* operator new(size_t size_, const char* file_, unsigned int line_);
	friend void operator delete(void* pointer, const char* file_, unsigned int line_);

	size_t          size;       //!< 要求されたメモリサイズ
	const char*     file;       //!< 要求された file 名
	unsigned int    line;       //!< 要求された行
	void*           address;    //!< 確保されたメモリのアドレス


	static std::list<MemoryData>* memoryList;    //!< 自分自身のインスタンス

public:


	/**----------------------------------------------------
	 * @brief     getter of size
	 * @return    Reference of size_t type.
	 *---------------------------------------------------*/
	static const size_t getSize() {
		return memoryList->size();
	}


	/**----------------------------------------------------
	 * @brief     getter of file
	 * @return    Reference of const char* type.
	 *---------------------------------------------------*/
	const char* getFile() const {
		return this->file;
	}


	/**----------------------------------------------------
	 * @brief     getter of line
	 * @return    Reference of unsigned int type.
	 *---------------------------------------------------*/
	unsigned int getLine() const {
		return this->line;
	}


	/**----------------------------------------------------
	 * @brief     getter of address
	 * @return    Reference of void* type.
	 *---------------------------------------------------*/
	unsigned long long int getAddress() const {
		return reinterpret_cast<unsigned long long int>(this->address);
	}


	/**----------------------------------------------------
	 * @brief     getter of address
	 * @return    Reference of void* type.
	 *---------------------------------------------------*/
	static void destroy() {
		if (memoryList != NULL) {
			delete memoryList;
		}
	}


	/**----------------------------------------------------
	 * @brief     現在持っているデータを全て出力する
	 *---------------------------------------------------*/
	static void printLeaksMemory() {
		std::list<MemoryData>::iterator ite;
		for (ite = memoryList->begin(); ite != memoryList->end(); ++ite) {
			std::cout << *ite << std::flush;
		}
	}



private:

	/**----------------------------------------------------
	 * @brief     constructor
	 *---------------------------------------------------*/
	MemoryData()
		: size(1)
		, file("")
		, line(0)
	{
		//memoryList = new MemoryData();
	}



	/**----------------------------------------------------
	 * @brief     getter of address
	 * @return    Reference of void* type.
	 *---------------------------------------------------*/
	static void create() {
		memoryList = new std::list<MemoryData>;
	}

public:

	/**----------------------------------------------------
	 * @brief  operator =
	 * @retval      true    equal
	 * @retval      false   not equal
	 *---------------------------------------------------*/
	bool operator ==(const MemoryData& data)
	{
		if (this->size == data.size
			&& this->file == data.file
			&& this->line == data.line)
		{
			return true;
		} else {
			return false;
		}
	}


	
	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os      ストリームオブジェクト
	 * @param[in]  team    出力オブジェクト
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const MemoryData& memory)
	{
		std::cout << "File name : " << memory.file << std::endl;
		std::cout << "line : " << memory.line << std::endl;
		std::cout << "size : " << memory.size << std::endl;

		return os;
	}

};
std::list<MemoryData>* ::MemoryData::memoryList = NULL;

/**--------------------------------------------------------
 * @brief ポインタが等しいかどうか比較するファンクタ
 * @author  Takuya Shishido
 * @date    2009/11/18 17:27
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
class PointerEqual : public std::binary_function<const MemoryData&, void*, bool>
{
public:
	/**----------------------------------------------------
	 * @brief  ファンクタ中身
	 * @param[in]   lhs     グローバルに持っているメモリデータ情報
	 * @param[in]   add     delete される際に渡されたアドレス
	 * @retval      true    add で指定されたアドレスが存在した
	 * @retval      false   存在しなかった
	 *---------------------------------------------------*/
	bool operator() (const MemoryData& lhs, void* add) const
	{
		if (lhs.address == add) {
			return true;
		} else {
			return false;
		}
	}

};



/**--------------------------------------------------------
 * @brief smart_ptr でもデータ管理ができる様に
 *          ファンクタを準備
 * @author  Takuya Shishido
 * @date    2009/11/18 17:27
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
class ManagedDeleter
{
public:
	/**----------------------------------------------------
	 * @brief  ファンクタ中身
	 * @param[in]   lhs     グローバルに持っているメモリデータ情報
	 * @param[in]   add     delete される際に渡されたアドレス
	 * @retval      true    add で指定されたアドレスが存在した
	 * @retval      false   存在しなかった
	 *---------------------------------------------------*/
	bool operator() (const MemoryData& lhs, void* add) const
	{
		if (lhs.address == add) {
			return true;
		} else {
			return false;
		}
	}

};



//---------------------------------------------------------
//  Define
//---------------------------------------------------------
//std::list<MemoryData> memoryList;
#define New new(__FILE__, __LINE__)
#define Delete(ptr) ::operator delete(ptr, __FILE__, __LINE__)



/**----------------------------------------------------
 * @brief  operator new
 *---------------------------------------------------*/
void* operator new(size_t size_, const char* file_, unsigned int line_) throw(std::bad_alloc)
{
	std::cout << file_ << ", line " << line_ << std::endl;

	if (::MemoryData::memoryList == NULL) {
		::MemoryData::memoryList = new std::list<MemoryData>;
	}

	// メモリ確保
	void* add;
	try {
		add = ::operator new(size_);
	} catch (...) {
		// メモリ確保失敗
		throw std::bad_alloc();
	}

	// メモリ管理情報作成
	MemoryData data;
	data.size = size_;
	data.file = file_;
	data.line = line_;
	data.address = add;

	// メモリ管理情報保管
	(::MemoryData::memoryList)->push_back(data);

	// 今回作成出来たデータを返還
	return add;
}



/**----------------------------------------------------
 * @brief  operator delete
 * @note    boost を使える場合と使えない場合でコードに差が出た。
 *          差が出た原因は C++ STL の言語的な仕様の都合による。
 *          std::bind2nd の引数にとられる関数の
 *          引数が reference をとる仕様になっていた場合
 *          reference to reference というバグ（要は参照の参照）
 *          が発生し、コンパイルが通らない。
 *          解決方は現状 boost を使うことだけのようだ。
 *---------------------------------------------------*/
void operator delete(void* pointer, const char* file_, unsigned int line_)
{
/*    // boost を使える場合のコード

	// ファイルの走査
	//std::list<MemoryData>::iterator ite = std::find_if(memoryList.begin(), memoryList.end(), boost::bind2nd(PointerEqual(), pointer));
	std::list<MemoryData>::iterator ite = std::find_if(memoryList.begin(), memoryList.end(), boost::bind(PointerEqual(), _1, pointer));

	// 上記の走査で見つからなかった場合
	if (ite == memoryList.end()) {
		std::cout << "メモリ破壊" << std::endl;
		std::cout << "file == " << file_ << std::endl;
		std::cout << "line == " << line_ << std::endl;
		std::cout << "address == " << (pointer) << std::endl;

	// 見つかった場合
	} else {
		memoryList.remove(*ite);
		free(pointer);
	}
*/


	// boost が使えない場合のループでの検索
	std::list<MemoryData>::iterator ite;    // メモリ管理コンテナを走査するイテレータ

	// リスト内の要素を全て走査し、今回消すオブジェクトとアドレスが一致すればリストから外す。
	//      過去の履歴と一致しなければメモリ破壊の可能性あり
	for (ite = ::MemoryData::memoryList->begin(); ite != ::MemoryData::memoryList->end(); ++ite) {
		if (ite->getAddress() == reinterpret_cast<unsigned long long int>(pointer)) {
			::MemoryData::memoryList->remove(*ite);
			delete pointer;
			return;
		}
	}

	// ここの行に達する場合は上記ループ検査で
	// 有効なデータが見つからなかった場合。
	// メモリ破壊の可能性がある
	std::cout << "メモリ破壊" << std::endl;
	std::cout << "file == " << file_ << std::endl;
	std::cout << "line == " << line_ << std::endl;
	std::cout << "address == " << reinterpret_cast<unsigned long long int>(pointer) << std::endl;

}

/**----------------------------------------------------
 * @brief  operator delete
 *---------------------------------------------------*/
/*void operator delete(void* pointer)
{
	//std::list<MemoryData>::iterator ite = std::find_if(memoryList.begin(), memoryList.end(), boost::bind2nd(PointerEqual(), pointer));
	std::list<MemoryData>::iterator ite = std::find_if(::MemoryData::memoryList->begin(), ::MemoryData::memoryList->end(), boost::bind(PointerEqual(), _1, pointer));

	free(pointer);
}*/



/**--------------------------------------------------------
 * @brief サンプルクラス
 * @author  Takuya Shishido
 * @date    2009/11/18 17:26
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
class Test
{
public:
	int integer;

	Test()
		: integer(2)
	{
	}

	~Test() {
		std::cout << "Called ~Test() Destructor!" << std::endl;
	}
};




//---------------------------------------------------------
//  entry point
//---------------------------------------------------------
int main()
{

{
	Test* test = New Test();

	std::cout << test->integer << std::endl;

	test->~Test();
	//::operator delete (test, __FILE__, __LINE__);
	Delete (test);

	{
		boost::shared_ptr<Test> test(new Test());
		std::cout << test->integer << std::endl;
	}

	Test test2;

}    // program end--------------------------------------------------


	// メモリに関するデータを保存している
	// コンテナにデータが残っているかチェック
	// 残っていた場合、メモリリークとなる
	if (::MemoryData::getSize() != 0) {
		std::cout << "Memory Leak!!!" << std::endl;
		::MemoryData::printLeaksMemory();
	}

	::MemoryData::destroy();

	_CrtDumpMemoryLeaks();	// この時点で開放されていないメモリの情報の表示
	return 0;
}

