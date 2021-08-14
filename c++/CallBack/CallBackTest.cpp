


#include <iostream>
#include <vector>


class NonCopyable
{
protected:
	NonCopyable () {}
	~NonCopyable () {}
private: 
	NonCopyable (const NonCopyable &);
	NonCopyable & operator = (const NonCopyable &);
};



class CallBackManager
	: NonCopyable
{
public:

	typedef void (*CallBackFunction)(int);      //!< type define for abstraction


	// get a instance
	static CallBackManager& GetInstance() throw() {
		static CallBackManager this_;
		return this_;
	}

	// add funciton to list
	void AddCallBack(CallBackFunction function) throw() {
		this->functionList_.push_back(function);
	}


	// call function with parameter
	void CallAllFunction(int integer) throw() {
		for (std::vector<CallBackFunction>::const_iterator ite = this->functionList_.begin(); ite < this->functionList_.end(); ++ite) {
			(*ite)(integer);
		}
	}

private:

	std::vector<CallBackFunction> functionList_;    //!< added callback function list
};


// a function to react a input
// this function is registered to CallBackManager
void printer(int integer) throw() {
	std::cerr << integer << std::endl;
}


int main() {
	CallBackManager& manager = CallBackManager::GetInstance();
	manager.AddCallBack(printer);

	// call functions
	manager.CallAllFunction(4);
}


