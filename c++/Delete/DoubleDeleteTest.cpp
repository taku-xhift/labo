
/**
 * @file
 * @brief delete を overload した際に remove でデータが無くなっているかのチェック用
 *
 * @author Takuya Shishido
 * @date   2009.11.30 16:57:35
 *
 * @version 0.01, Shishido Takuya, 2009.11.30 16:57:35
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#include <iostream>
#include <list>




//---------------------------------------------------------
//  Define
//---------------------------------------------------------
//std::list<MemoryData> memoryList;
#define New new(__FILE__, __LINE__)
#define Delete(ptr) ::operator delete(ptr, __FILE__, __LINE__)



class MemoryData;
std::list<MemoryData> memoryList;



/**
 * @brief チェック用のデータクラス
 *          
 * @author  Takuya Shishido
 * @date    2009.11.30 16:57:35
 * @version 0.01, Shishido Takuya, 2009.11.30 16:57:35
 */
class MemoryData
{
private:

	friend void* operator new(size_t size_, const char* file_, unsigned int line_);
	friend void operator delete(void* pointer, const char* file_, unsigned int line_);

	size_t          size;       //!< 要求されたメモリサイズ
	const char*     file;       //!< 要求された file 名
	unsigned int    line;       //!< 要求された行
	void*           address;    //!< 確保されたメモリのアドレス

public:


	/**----------------------------------------------------
	 * @brief     getter of size
	 * @return    Reference of size_t type.
	 *---------------------------------------------------*/
	static const size_t getSize() {
		return memoryList.size();
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
	unsigned int getAddress() const {
		return reinterpret_cast<unsigned int>(this->address);
	}


	/**----------------------------------------------------
	 * @brief     getter of address
	 * @return    Reference of void* type.
	 *---------------------------------------------------*/
	static void create() {
		//memoryList = new std::list<MemoryData>;
	}


	/**----------------------------------------------------
	 * @brief     現在持っているデータを全て出力する
	 *---------------------------------------------------*/
	static void printLeaksMemory() {
		std::list<MemoryData>::iterator ite;
		for (ite = memoryList.begin(); ite != memoryList.end(); ++ite) {
			std::cout << *ite << std::flush;
		}
	}




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


/**----------------------------------------------------
 * @brief  operator new
 *---------------------------------------------------*/
void* operator new(size_t size_, const char* file_, unsigned int line_)
{
	std::cout << file_ << ", line " << line_ << std::endl;

	//void* add = malloc(size_);
	void* add = ::operator new(size_);
	MemoryData data;
	data.size = size_;
	data.file = file_;
	data.line = line_;
	data.address = add;
	memoryList.push_back(data);

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
	// boost が使えない場合のループでの検索
	std::list<MemoryData>::iterator ite;    // メモリ管理コンテナを走査するイテレータ

	// リスト内の要素を全て走査し、今回消すオブジェクトとアドレスが一致すればリストから外す。
	//      過去の履歴と一致しなければメモリ破壊の可能性あり
	for (ite = memoryList.begin(); ite != memoryList.end(); ++ite) {
		if (ite->getAddress() == reinterpret_cast<unsigned int>(pointer)) {
			memoryList.remove(*ite);
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
	std::cout << "address == " << reinterpret_cast<unsigned int>(pointer) << std::endl;

}



class Test { public: Test() : integer(3) { }
public: int integer;
};



int main()
{
	Test* test = New Test();

	Delete(test);

	return 0;
}


