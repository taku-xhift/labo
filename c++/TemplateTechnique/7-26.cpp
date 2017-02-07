


#include <iostream>
#include <typeinfo>

class any
{
	struct holder_base
	{
		virtual ~holder_base() {}
		virtual holder_base* clone() const = 0;
		virtual const std::type_info& type() const = 0;
	};

	template<typename T>
	struct holder : public holder_base
	{
		T value_;

		holder(const T &value)
			: value_(value)
		{
		}

		virtual holder_base* clone() const
		{
			return new holder(value_);
		}

		virtual const std::type_info& type() const
		{
			return typeid(T);
		}
	};

	holder_base *content_;


public:

	template<typename T>
	any(const T &value)
		: content_(new holder<T>(value)) {}

	~any()
	{

		delete this->content_;
	}

	any(const any& other)
		: content_(other.content_ ? other.content_->clone() : 0;

	template<typename T>
	any &operator=(const T& value)
	{
		delete this->content_;
		this->content_ = new holder<T>(value);
		return *this;
	}

	template<>
	any& operator=(const any& other)
	{
		delete this->content_;
		this->content_ = other.content_ ? other.content_->clone() : 0;
		return *this;
	}

};

struct hoge
{
	hoge()
	{
		std::cout << "hoge" << std::endl;
	}
};

int main()
{
	any val = 3;

	val = hoge();


	return 0;
}


