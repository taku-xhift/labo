
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
 * @brief �`�F�b�N�p�̃f�[�^�N���X
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

	size_t          size;       //!< �v�����ꂽ�������T�C�Y
	const char*     file;       //!< �v�����ꂽ file ��
	unsigned int    line;       //!< �v�����ꂽ�s
	void*           address;    //!< �m�ۂ��ꂽ�������̃A�h���X

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
	 * @brief     ���ݎ����Ă���f�[�^��S�ďo�͂���
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
	// boost ���g���Ȃ��ꍇ�̃��[�v�ł̌���
	std::list<MemoryData>::iterator ite;    // �������Ǘ��R���e�i�𑖍�����C�e���[�^

	// ���X�g���̗v�f��S�đ������A��������I�u�W�F�N�g�ƃA�h���X����v����΃��X�g����O���B
	//      �ߋ��̗����ƈ�v���Ȃ���΃������j��̉\������
	for (ite = memoryList.begin(); ite != memoryList.end(); ++ite) {
		if (ite->getAddress() == reinterpret_cast<unsigned int>(pointer)) {
			memoryList.remove(*ite);
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


