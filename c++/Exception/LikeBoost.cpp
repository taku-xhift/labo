


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
			// 出来ることがない
		}
	}


	//! \brief ログ情報を追加する
	//! \param[in]  log     新しい情報
	//! \return     連続して << で追加するために自分自身を返却
	virtual Exception& operator<<(const std::string& log) throw() {
		try {
			this->messageList_.push_back(log + "\n");
		} catch (std::bad_alloc) {
			// 出来ることがない
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


	//! \brief 持っている情報をすべて string にまとめて返す
	//! \return     << で足されたものを含む全ての情報
	std::string getAllInfo() const throw(std::bad_alloc) {
		std::string returnValue = this->what();

		// １つめに関しては what で出力されているのでここでは返さない
		std::vector<std::string>::const_iterator ite = this->messageList_.begin();
		advance(ite, 1);
		for (; ite != this->messageList_.end(); ++ite) {
			returnValue.append("↑\n");
			returnValue.append(*ite);
		}
		return returnValue;
	}

protected:

	//! \brief destructor
	//! \note   virtual でなくていい
	~Exception() throw() { std::cout << "destructed!!!" << std::endl; }


	//! \brief 型情報を返す
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



