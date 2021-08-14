


#include <iostream>
#include <typeinfo>


class any
{
	// anTemplate base class
	struct holder_base {
		virtual ~holder_base() {}
		virtual holder_base* clone() const = 0;
		virtual const std::type_info& type() const = 0;
	};

	// Template derived class
	template<typename T>
	struct holder : public holder_base {

		T value_;    // データ本体

		// constructor
		holder(const T& value)
			: value_(value) {}

		// コピー用関数
		virtual holder_base* clone() const
		{
			return new holder(value_);
		}

		// 型判別
		virtual const std::type_info& type() const
		{
			return typeid(T);
		}
	};

public:

	//--------------------------------
	//  動的な型の切り替え
	//--------------------------------

	// constructor
	template<typename T>
	any(const T& value)
		 : content_(new holder<T>(value)) {}

	// destructor
	~any()
	{
		delete this->content_;
	}

	// operator =
	template<typename T>
	any& operator =(const T& value)
	{
		delete this->content_;
		this->content_ = new holder<T>(value);
		return *this;
	}

	// copy constructor
	any(const any& other)
		 : content_(other.content_ ? other.content_->clone() : NULL) {}

	// operator =
	any& operator=(const any& other)
	{
		delete this->content_;
		this->content_ = other.content_ ? other.content_->clone() : NULL;
		return *this;
	}

	// 型判別
	const std::type_info& type() const
	{
		return this->content_ ? this->content_->type() : typeid(void);
	}

	// データ取得
	template<typename T>
	const T& cast() const
	{
		return dynamic_cast<holder<T>& >(*content_).value_;
	}

private:
	holder_base* content_;  // データ本体
};

struct hoge
{
	float floating;

	hoge() {
		this->floating = 220.0f;
	}

};


int main()
{
	any data = 0;

	data = hoge();

	if (data.type() == typeid(int)) {
		int value = data.cast<int>();
		std::cout << value << std::endl;
	} else if (data.type() == typeid(hoge)) {
		hoge h = data.cast<hoge>();
		std::cout << h.floating << std::endl;
	}

	return 0;
}

