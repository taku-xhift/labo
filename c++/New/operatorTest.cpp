
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
 * @brief �������f�[�^�Ǘ��N���X
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

	size_t          size;       //!< �v�����ꂽ�������T�C�Y
	const char*     file;       //!< �v�����ꂽ file ��
	unsigned int    line;       //!< �v�����ꂽ�s
	void*           address;    //!< �m�ۂ��ꂽ�������̃A�h���X


	static std::list<MemoryData>* memoryList;    //!< �������g�̃C���X�^���X

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
	 * @brief     ���ݎ����Ă���f�[�^��S�ďo�͂���
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
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os      �X�g���[���I�u�W�F�N�g
	 * @param[in]  team    �o�̓I�u�W�F�N�g
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
 * @brief �|�C���^�����������ǂ�����r����t�@���N�^
 * @author  Takuya Shishido
 * @date    2009/11/18 17:27
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
class PointerEqual : public std::binary_function<const MemoryData&, void*, bool>
{
public:
	/**----------------------------------------------------
	 * @brief  �t�@���N�^���g
	 * @param[in]   lhs     �O���[�o���Ɏ����Ă��郁�����f�[�^���
	 * @param[in]   add     delete �����ۂɓn���ꂽ�A�h���X
	 * @retval      true    add �Ŏw�肳�ꂽ�A�h���X�����݂���
	 * @retval      false   ���݂��Ȃ�����
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
 * @brief smart_ptr �ł��f�[�^�Ǘ����ł���l��
 *          �t�@���N�^������
 * @author  Takuya Shishido
 * @date    2009/11/18 17:27
 * @version 0.01, Shishido Takuya, 2009/11/18 17:27
 *-------------------------------------------------------*/
class ManagedDeleter
{
public:
	/**----------------------------------------------------
	 * @brief  �t�@���N�^���g
	 * @param[in]   lhs     �O���[�o���Ɏ����Ă��郁�����f�[�^���
	 * @param[in]   add     delete �����ۂɓn���ꂽ�A�h���X
	 * @retval      true    add �Ŏw�肳�ꂽ�A�h���X�����݂���
	 * @retval      false   ���݂��Ȃ�����
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

	// �������m��
	void* add;
	try {
		add = ::operator new(size_);
	} catch (...) {
		// �������m�ێ��s
		throw std::bad_alloc();
	}

	// �������Ǘ����쐬
	MemoryData data;
	data.size = size_;
	data.file = file_;
	data.line = line_;
	data.address = add;

	// �������Ǘ����ۊ�
	(::MemoryData::memoryList)->push_back(data);

	// ����쐬�o�����f�[�^��Ԋ�
	return add;
}



/**----------------------------------------------------
 * @brief  operator delete
 * @note    boost ���g����ꍇ�Ǝg���Ȃ��ꍇ�ŃR�[�h�ɍ����o���B
 *          �����o�������� C++ STL �̌���I�Ȏd�l�̓s���ɂ��B
 *          std::bind2nd �̈����ɂƂ���֐���
 *          ������ reference ���Ƃ�d�l�ɂȂ��Ă����ꍇ
 *          reference to reference �Ƃ����o�O�i�v�͎Q�Ƃ̎Q�Ɓj
 *          ���������A�R���p�C�����ʂ�Ȃ��B
 *          �������͌��� boost ���g�����Ƃ����̂悤���B
 *---------------------------------------------------*/
void operator delete(void* pointer, const char* file_, unsigned int line_)
{
/*    // boost ���g����ꍇ�̃R�[�h

	// �t�@�C���̑���
	//std::list<MemoryData>::iterator ite = std::find_if(memoryList.begin(), memoryList.end(), boost::bind2nd(PointerEqual(), pointer));
	std::list<MemoryData>::iterator ite = std::find_if(memoryList.begin(), memoryList.end(), boost::bind(PointerEqual(), _1, pointer));

	// ��L�̑����Ō�����Ȃ������ꍇ
	if (ite == memoryList.end()) {
		std::cout << "�������j��" << std::endl;
		std::cout << "file == " << file_ << std::endl;
		std::cout << "line == " << line_ << std::endl;
		std::cout << "address == " << (pointer) << std::endl;

	// ���������ꍇ
	} else {
		memoryList.remove(*ite);
		free(pointer);
	}
*/


	// boost ���g���Ȃ��ꍇ�̃��[�v�ł̌���
	std::list<MemoryData>::iterator ite;    // �������Ǘ��R���e�i�𑖍�����C�e���[�^

	// ���X�g���̗v�f��S�đ������A��������I�u�W�F�N�g�ƃA�h���X����v����΃��X�g����O���B
	//      �ߋ��̗����ƈ�v���Ȃ���΃������j��̉\������
	for (ite = ::MemoryData::memoryList->begin(); ite != ::MemoryData::memoryList->end(); ++ite) {
		if (ite->getAddress() == reinterpret_cast<unsigned long long int>(pointer)) {
			::MemoryData::memoryList->remove(*ite);
			delete pointer;
			return;
		}
	}

	// �����̍s�ɒB����ꍇ�͏�L���[�v������
	// �L���ȃf�[�^��������Ȃ������ꍇ�B
	// �������j��̉\��������
	std::cout << "�������j��" << std::endl;
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
 * @brief �T���v���N���X
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


	// �������Ɋւ���f�[�^��ۑ����Ă���
	// �R���e�i�Ƀf�[�^���c���Ă��邩�`�F�b�N
	// �c���Ă����ꍇ�A���������[�N�ƂȂ�
	if (::MemoryData::getSize() != 0) {
		std::cout << "Memory Leak!!!" << std::endl;
		::MemoryData::printLeaksMemory();
	}

	::MemoryData::destroy();

	_CrtDumpMemoryLeaks();	// ���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
	return 0;
}

