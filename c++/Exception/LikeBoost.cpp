


#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>


class Exception
	: public std::exception
{
public:

	Exception(const std::string& log) throw() {
		try {
			this->messageList_.push_back(log);
		} catch (std::bad_alloc) {
			// �o���邱�Ƃ��Ȃ�
		}
	}


	//! \brief ���O����ǉ�����
	//! \param[in]  log     �V�������
	//! \return     �A������ << �Œǉ����邽�߂Ɏ������g��ԋp
	virtual Exception& operator<<(const std::string& log) throw() {
		try {
			this->messageList_.push_back(log + "\n");
		} catch (std::bad_alloc) {
			// �o���邱�Ƃ��Ȃ�
		}
		return *this;
	}

	virtual const char* what() const throw() {
		if (this->messageList_.empty() != true) {
			return ("Type[" + this->getType() + "]\n" + "Thrown from " + this->messageList_.at(0) + "\n").c_str();
		} else {
			return ("Type[" + this->getType() + "]").c_str();
		}
	}


	//! \brief �����Ă���������ׂ� string �ɂ܂Ƃ߂ĕԂ�
	//! \return     << �ő����ꂽ���̂��܂ޑS�Ă̏��
	std::string getAllInfo() const throw(std::bad_alloc) {
		std::string returnValue = this->what();

		// �P�߂Ɋւ��Ă� what �ŏo�͂���Ă���̂ł����ł͕Ԃ��Ȃ�
		std::vector<std::string>::const_iterator ite = this->messageList_.begin();
		advance(ite, 1);
		for (; ite != this->messageList_.end(); ++ite) {
			returnValue.append("��\n");
			returnValue.append(*ite);
		}
		return returnValue;
	}

protected:

	//! \brief destructor
	//! \note   virtual �łȂ��Ă���
	~Exception() throw() { std::cout << "destructed!!!" << std::endl; }


	//! \brief �^����Ԃ�
	virtual std::string getType() const throw() { return ""; }

private:
	std::vector<std::string> messageList_;
};




class Derived
	: public Exception
{
public:
	Derived(const char* const log) throw()
		: Exception(log)
	{
		
	}

	std::string getType() const throw() { return "Derived"; }
};


int main() {
	try {
		throw Derived("Exception");
	} catch (Exception& ex) {
		ex << "test";
		ex << "sample";
		std::cout << ex.getAllInfo() << std::endl;
	}

}



