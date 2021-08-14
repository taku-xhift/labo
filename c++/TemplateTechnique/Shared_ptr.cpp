

#include <iostream>
#include <vector>



class shared_deleter_base
{
public:
	shared_deleter_base() {}
	virtual ~shared_deleter_base() {}
	virtual void destroy() = 0;
};

template<typename T, typename D>
class shared_deleter : public shared_deleter_base
{
	T *object_;
	D deleter_;

public:

	shared_deleter(T *object, D deleter)
		: object_(object)
		, deleter_(deleter)
	{
	}

	virtual void destroy()
	{
		this->deleter_(this->object_);
	}
};



template<typename T>
class shared_ptr
{
	T *object_;
	shared_deleter_base *deleter_;

public:

	explicit shared_ptr(T *object)
		: object_(object)
		, deleter_(NULL)
	{
	}

	template<typename D>
	shared_ptr(T *object, D deleter)
		: object_(object)
	{
		this->deleter_ = new shared_deleter<T, D>(object_, deleter);
	}

	~shared_ptr()
	{
		if (this->deleter_) {
			deleter_->destroy();
			delete deleter_;
		} else {
			delete this->object_;
		}
	}

	T* operator->() const
	{
		return this->object_;
	}
};


struct hoge
{
	hoge() {
		std::cout << "Constructor" << std::endl;
	}

	~hoge() {
		std::cout << "Destrutor" << std::endl;
	}

	void something() {
		std::cout << "Something" << std::endl;
	}
};


void delete_hoge(hoge *hoge)
{
	delete hoge;
	std::cout << "Free by deleter." << std::endl;
}


void foo()
{
	shared_ptr<hoge> p(new hoge(), &delete_hoge);
	p->something();
}


int main()
{
	shared_ptr<hoge> p(new hoge());


	//foo();
	{
		std::vector<shared_ptr<hoge> > container;

		shared_ptr<hoge> pointer = p;
		container.push_back(pointer);
	}

	p->something();
	std::cout << "Out of scope." << std::endl;

	return 0;
}

